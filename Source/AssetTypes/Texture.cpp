#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture()
{
	x, y, n = 0;
	data == NULL;
}

Texture::Texture(const char* filename)
{
	data = stbi_load(filename, &x, &y, &n, 0);
	assert(data != NULL);
}


Texture::~Texture()
{
	stbi_image_free(data);
}

vec3 Texture::GetPixel(int X, int Y)
{
	if (X > x || Y > y)
		return vec3();

	vec3 colour;

	int pLoc = (x*Y + X) * 3;
	unsigned char R = data[pLoc];
	unsigned char G = data[pLoc + 1];
	unsigned char B = data[pLoc + 2];

	colour.x = R;
	colour.y = G;
	colour.z = B;

	return colour;
}
