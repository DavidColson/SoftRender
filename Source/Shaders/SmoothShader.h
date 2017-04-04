#pragma once
#include "Shader.h"
class SmoothShader : public Shader
{
public:
	Maths::Vec4f Vertex(int iFace, int nthVert);
	bool Fragment(Maths::Vec3f barycentric, Maths::Vec3f &Colour);
private:
	Maths::Vec3f intensity;
};

