#include "Scene.h"
#include "Maths.h"
#include <algorithm>
#include <limits>


Scene::Scene(int screenWidth, int screenHeight)
{
	height = screenHeight;
	width = screenWidth;
	// Create the SDL surface
	Uint32 rmask, gmask, bmask, amask;

	/* SDL interprets each pixel as a 32-bit number, so our masks must depend
	on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	surf = SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);

	zBuffer = new float[surf->w * surf->h];
}


Scene::~Scene()
{
	delete zBuffer;
}

void Scene::AddObject(SceneObject* newObject)
{
	// Push into vector
	objects.push_back(newObject);
}

SDL_Surface* Scene::Render()
{
	
	for (int i = 0; i < surf->w * surf->h; i++)
	{
		zBuffer[i] = std::numeric_limits<float>::max();
	}

	// Clear the surface
	for (int y = 0; y < surf->h; y++)
	{
		for (int x = 0; x < surf->w; x++)
		{
			SetSurfacePixel(surf, x, y, 0xFFED9564);
		}
	}

	// Render all the objects
	// TODO: Sort by model depth
	for (SceneObject* o : objects)
	{
		// Model Matrix, converts to world space
		Maths::Mat4f scale = Maths::MakeScale(o->scale); 
		Maths::Mat4f translate = Maths::MakeTranslate(o->position);
		Maths::Mat4f rotate = Maths::MakeRotate(o->rotation);

		// Move objects backward from the camera's position
		Maths::Mat4f cameraTranslate = Maths::MakeTranslate(Maths::Vec3f(-cameraPosition.X, -cameraPosition.Y, -cameraPosition.Z));

		// Get the camera's rotated basis vectors to rotate everything to camera space.
		Maths::Vec3f Forward;
		Maths::Vec3f Right;
		Maths::Vec3f Up;
		Maths::GetAxesFromRotation(cameraRotation, Forward, Right, Up);
		Maths::Mat4f cameraRotate = Maths::MakeLookAt(Forward, Up);

		// Convert from camera space to perspective projection space
		Maths::Mat4f projection = Maths::MakePerspective(surf->w, surf->h, 1, 10, cameraFOV);

		// Convert from projection space (-1, 1) to viewport space
		Maths::Mat4f viewport = Maths::MakeViewport(surf->w, surf->h);

		Maths::Mat4f Model = translate * rotate * scale;
		Maths::Mat4f MVP = viewport * projection * cameraRotate * cameraTranslate * Model;

		int nFaces = o->model->faces.size();
		for (int i = 0; i < nFaces; i++)
		{
			Maths::Vec3f trianglePoints[3];
			for (int j = 0; j < 3; j++)
			{
				// Prepare and run the vertex shader for all the vertices of this triangle
				o->shader->MVP = MVP;
				o->shader->M = cameraRotate * cameraTranslate * Model;
				o->shader->model = o->model;
				Maths::Vec4f pos = o->shader->Vertex(i, j);

				// Perspective divide
				pos = Maths::Vec4f(pos.X / pos.W, pos.Y / pos.W, pos.Z / pos.W, 1.0);
				trianglePoints[j] = Maths::Vec3f(int(pos.X), int(pos.Y), int(pos.Z));
			}
			DrawTriangle(o->shader, trianglePoints[0], trianglePoints[1], trianglePoints[2]);
		}
	}
	
	return surf;
}
bool Scene::BarycentricTriangle(Maths::Vec3f* poly)
{
	det = 1.0 / ((poly[1].Y - poly[2].Y) * (poly[0].X - poly[2].X) + (poly[2].X - poly[1].X) * (poly[0].Y - poly[2].Y));
	if (det == 0)
	{
		return false;
	}
	return true;
}

void Scene::BarycentricPoint(Maths::Vec3f* poly, Maths::Vec3f* P, Maths::Vec3f* outbcoords)
{
	outbcoords->X = ((poly[1].Y - poly[2].Y) * (P->X - poly[2].X) + (poly[2].X - poly[1].X) * (P->Y - poly[2].Y)) * det;
	outbcoords->Y = ((poly[2].Y - poly[0].Y) * (P->X - poly[2].X) + (poly[0].X - poly[2].X) * (P->Y - poly[2].Y)) * det;
	outbcoords->Z = 1 - outbcoords->X - outbcoords->Y;
}

void Scene::DrawTriangle(Shader* shader, Maths::Vec3f v1, Maths::Vec3f v2, Maths::Vec3f v3)
{
	// Calculate a bounding box for this triangle
	Maths::Vec2f bbmin(surf->w, surf->h);
	Maths::Vec2f bbmax(0, 0);
	Maths::Vec2f clamp(surf->w, surf->h);
	Maths::Vec3f points[3] = { v1, v2, v3 };
	for (int i = 0; i < 3; i++)
	{
		bbmin.X = std::max(0.0, (double)std::min(bbmin.X, points[i].X));
		bbmin.Y = std::max(0.0, (double)std::min(bbmin.Y, points[i].Y));
		bbmax.Y = std::min(clamp.Y, std::max(bbmax.Y, points[i].Y));
		bbmax.X = std::min(clamp.X, std::max(bbmax.X, points[i].X));
	}

	// Looping over every pixel in the bounding box
	Maths::Vec3f P;
	Maths::Vec3f bc;
	if (!BarycentricTriangle(points))
	{
		return;
	}
	for (P.X = bbmin.X; P.X <= bbmax.X; P.X++) {
		for (P.Y = bbmin.Y; P.Y <= bbmax.Y; P.Y++) {
			// If any of the barycentric coordinates are negative, this pixel is not inside the triangle
			BarycentricPoint(points, &P, &bc);
			if (bc.X < 0 || bc.Y < 0 || bc.Z < 0) continue;
			P.Z = 0;
			P.Z += points[0].Z * bc.X;
			P.Z += points[1].Z * bc.Y;
			P.Z += points[2].Z * bc.Z;
			if (P.Y > surf->h - 1 || P.X > surf->w - 1) continue;

			int id = int(P.X) + int(P.Y) * surf->w;
			if (zBuffer[id] > P.Z)
			{
				zBuffer[id] = P.Z;

				// Call the fragment shader for each pixel, giving it the barycentric coordinates so it can interpolate vertex data.
				Maths::Vec3f cVec;
				if (shader->Fragment(bc, cVec))
				{
					Uint32 colour = SDL_MapRGB(surf->format, cVec.X, cVec.Y, cVec.Z);
					SetSurfacePixel(surf, P.X, P.Y, colour);
				}
				// Visualise Depth buffer 
				//SetSurfacePixel(surf, P.X, P.Y, SDL_MapRGB(surf->format, abs(P.Z)*1, abs(P.Z)*1, abs(P.Z)*1));
			}
		}
	}
}

void Scene::DrawLine(SDL_Surface* surf, int x0, int y0, int x1, int y1, Uint32 Colour)
{
	int w = x1 - x0;
	int h = y1 - y0;
	int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0;
	if (w<0) dx1 = -1; else if (w>0) dx1 = 1;
	if (h<0) dy1 = -1; else if (h>0) dy1 = 1;
	if (w<0) dx2 = -1; else if (w>0) dx2 = 1;
	int longest = abs(w);
	int shortest = abs(h);
	if (!(longest>shortest)) {
		longest = abs(h);
		shortest = abs(w);
		if (h<0) dy2 = -1; else if (h>0) dy2 = 1;
		dx2 = 0;
	}
	int x = x0;
	int y = y0;
	int numerator = longest >> 1;
	for (int i = 0; i <= longest; i++) {
		SetSurfacePixel(surf, x, y, Colour);
		numerator += shortest;
		if (!(numerator<longest)) {
			numerator -= longest;
			x += dx1;
			y += dy1;
		}
		else {
			x += dx2;
			y += dy2;
		}
	}
}

void Scene::SetSurfacePixel(SDL_Surface* surf, int x, int y, Uint32 Colour)
{
	if ((x <= surf->w && y <= surf->h) && (x >= 0 && y >= 0))
	{
		Uint32* pixel = (Uint32*)surf->pixels;
		pixel += ((surf->h - y) * surf->w) + x;
		*pixel = Colour;
	}
}