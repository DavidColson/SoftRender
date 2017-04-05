#pragma once

#include "SDL.h"
#include "Model.h"
#include "SceneObject.h"
#include <vector>

class Scene
{
public:
	Scene(int screenWidth, int screenHeight);
	~Scene();

	SDL_Surface* Render();

	// Note, the scene takes control of the newObject lifetime. Do not delete it, the Scene will do it.
	void AddObject(SceneObject* newObject);

	vec3 cameraPosition;
	vec3 cameraRotation;
	float cameraFOV = 60.f;

private:
	int width;
	int height;

	// Render buffers
	SDL_Surface* surf;
	float* zBuffer;

	std::vector<SceneObject*> objects;

	// Calculate barycentric coordinates for a given point P inside a triangle defined by Poly, returning bcoords.
	bool BarycentricTriangle(vec3 *poly);
	void BarycentricPoint(vec3 *poly, vec3* P, vec3* bcoords);
	double det;

	void DrawLine(SDL_Surface* surf, int x0, int y0, int x1, int y1, Uint32 Colour);
	void DrawTriangle(Shader* shader, vec3 v1, vec3 v2, vec3 v3);

	void SetSurfacePixel(SDL_Surface* surf, int x, int y, Uint32 Colour);
};

