#pragma once
#include "Maths.h"

class Texture
{
public:
	Texture();
	Texture(const char* filename);
	~Texture();

	vec3 GetPixel(int X, int Y);

private:
	int x, y, n;
	unsigned char* data;
};

