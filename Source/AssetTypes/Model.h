#pragma once
#include <vector>
#include "Maths.h"

class Model
{
	friend class Scene;
public:
	Model(const char* filename);

	vec3 Model::vert(int iface, int nthvert);
	vec2 Model::uv(int iface, int nthvert);
	vec3 Model::normal(int iface, int nthvert);

private:
	std::vector<vec3> verts;
	std::vector<std::vector<vec3>> faces;
	std::vector<vec3> normals;
	std::vector<vec2> uvs;
};

