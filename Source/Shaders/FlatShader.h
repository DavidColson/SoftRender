#pragma once
#include "Shader.h"
#include "Scene.h"

class FlatShader : public Shader
{
public:
	Maths::Vec4f Vertex(int iFace, int nthVert);
	bool Fragment(Maths::Vec3f barycentric, Maths::Vec3f &Colour);
private:
	float faceIntensity;
};
