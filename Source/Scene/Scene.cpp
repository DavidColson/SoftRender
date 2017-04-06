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
		mat4 scale = MakeScale(o->scale); 
		mat4 translate = MakeTranslate(o->position);
		mat4 rotate = MakeRotate(o->rotation);

		// Move objects backward from the camera's position
		mat4 cameraTranslate = MakeTranslate(vec3(-cameraPosition.x, -cameraPosition.y, -cameraPosition.z));

		// Get the camera's rotated basis vectors to rotate everything to camera space.
		vec3 Forward;
		vec3 Right;
		vec3 Up;
		GetAxesFromRotation(cameraRotation, Forward, Right, Up);
		mat4 cameraRotate = MakeLookAt(Forward, Up);

		// Convert from camera space to perspective projection space
		mat4 projection = MakePerspective(surf->w, surf->h, 1, 10, cameraFOV);

		// Convert from projection space (-1, 1) to viewport space
		mat4 viewport = MakeViewport(surf->w, surf->h);

		mat4 Model = translate * rotate * scale;
		mat4 MVP = viewport * projection * cameraRotate * cameraTranslate * Model;

		int nFaces = o->model->faces.size();
		for (int i = 0; i < nFaces; i++)
		{
			vec3 trianglePoints[3];
			for (int j = 0; j < 3; j++)
			{
				// Prepare and run the vertex shader for all the vertices of this triangle
				o->shader->MVP = MVP;
				o->shader->M = Model;
				o->shader->model = o->model; 
				vec4 pos = o->shader->Vertex(i, j);

				// Perspective divide
				pos = vec4(pos.x / pos.w, pos.y / pos.w, pos.z / pos.w, 1.0);
				trianglePoints[j] = vec3(int(pos.x), int(pos.y), int(pos.z));
			}
			DrawTriangle(o->shader, trianglePoints[0], trianglePoints[1], trianglePoints[2]);
		}
	}
	
	return surf;
}
bool Scene::BarycentricTriangle(vec3* poly)
{
	det = 1.0 / ((poly[1].y - poly[2].y) * (poly[0].x - poly[2].x) + (poly[2].x - poly[1].x) * (poly[0].y - poly[2].y));
	if (det == 0)
	{
		return false;
	}
	return true;
}

void Scene::BarycentricPoint(vec3* poly, vec3* P, vec3* outbcoords)
{
	outbcoords->x = ((poly[1].y - poly[2].y) * (P->x - poly[2].x) + (poly[2].x - poly[1].x) * (P->y - poly[2].y)) * det;
	outbcoords->y = ((poly[2].y - poly[0].y) * (P->x - poly[2].x) + (poly[0].x - poly[2].x) * (P->y - poly[2].y)) * det;
	outbcoords->z = 1 - outbcoords->x - outbcoords->y;
}

void Scene::DrawTriangle(Shader* shader, vec3 v1, vec3 v2, vec3 v3)
{
	// Calculate a bounding box for this triangle
	vec2 bbmin(surf->w, surf->h);
	vec2 bbmax(0, 0);
	vec2 clamp(surf->w, surf->h);
	vec3 points[3] = { v1, v2, v3 };
	for (int i = 0; i < 3; i++)
	{
		bbmin.x = std::max(0.0, (double)std::min(bbmin.x, points[i].x));
		bbmin.y = std::max(0.0, (double)std::min(bbmin.y, points[i].y));
		bbmax.y = std::min(clamp.y, std::max(bbmax.y, points[i].y));
		bbmax.x = std::min(clamp.x, std::max(bbmax.x, points[i].x));
	}

	// Looping over every pixel in the bounding box
	vec3 P;
	vec3 bc;
	if (!BarycentricTriangle(points))
	{
		return;
	}
	for (P.x = bbmin.x; P.x <= bbmax.x; P.x++) {
		for (P.y = bbmin.y; P.y <= bbmax.y; P.y++) {
			// If any of the barycentric coordinates are negative, this pixel is not inside the triangle
			BarycentricPoint(points, &P, &bc);
			if (bc.x < 0 || bc.y < 0 || bc.z < 0) continue;
			P.z = 0;
			P.z += points[0].z * bc.x;
			P.z += points[1].z * bc.y;
			P.z += points[2].z * bc.z;
			if (P.y > surf->h - 1 || P.x > surf->w - 1) continue;

			int id = int(P.x) + int(P.y) * surf->w;
			if (zBuffer[id] > P.z)
			{
				zBuffer[id] = P.z;

				// Call the fragment shader for each pixel, giving it the barycentric coordinates so it can interpolate vertex data.
				vec3 cVec;
				if (shader->Fragment(bc, cVec))
				{
					Uint32 colour = SDL_MapRGB(surf->format, cVec.x, cVec.y, cVec.z);
					SetSurfacePixel(surf, P.x, P.y, colour);
				}
				// Visualise Depth buffer 
				//SetSurfacePixel(surf, P.x, P.y, SDL_MapRGB(surf->format, abs(P.z)*1, abs(P.z)*1, abs(P.z)*1));
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