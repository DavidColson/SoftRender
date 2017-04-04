#pragma once

#include "Maths.h"
#include "Model.h"

class Shader
{
	friend class Scene;

public:
	virtual Maths::Vec4f Vertex(int iFace, int nthVert) = 0;
	virtual bool Fragment(Maths::Vec3f barycentric, Maths::Vec3f &Colour) = 0;

protected:
	Maths::Mat4f MVP; // Model View Projection
	Maths::Mat4f M;   // Model (world coordinates)
	Model* model;     // model data (verts, normals, uvs)
};

