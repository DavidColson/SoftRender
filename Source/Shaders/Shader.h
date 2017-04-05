#pragma once

#include "Maths.h"
#include "Model.h"

class Shader
{
	friend class Scene;

public:
	virtual vec4 Vertex(int iFace, int nthVert) = 0;
	virtual bool Fragment(vec3 barycentric, vec3 &Colour) = 0;

protected:
	mat4 MVP; // Model View Projection
	mat4 M;   // Model (world coordinates)
	Model* model;     // model data (verts, normals, uvs)
};

