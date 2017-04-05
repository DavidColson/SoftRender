#pragma once
#include "Shader.h"
class SmoothShader : public Shader
{
public:
	vec4 Vertex(int iFace, int nthVert);
	bool Fragment(vec3 barycentric, vec3 &Colour);
private:
	vec3 intensity;
};

