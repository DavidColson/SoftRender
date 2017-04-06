#pragma once
#include "Shader.h"
#include "Texture.h"
class TextureShader : public Shader
{
public:
	Texture* diffuse;
	vec4 Vertex(int iFace, int nthVert);
	bool Fragment(vec3 barycentric, vec3 &Colour);
private:
	vec3 intensity;
	mat<2, 3, float> uvs;
};

