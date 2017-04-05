#pragma once
#include "Shader.h"
#include "Scene.h"

class FlatShader : public Shader
{
public:
	vec4 Vertex(int iFace, int nthVert);
	bool Fragment(vec3 barycentric, vec3 &Colour);
private:
	float faceIntensity;
};
