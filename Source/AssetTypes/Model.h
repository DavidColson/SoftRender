#pragma once
#include <vector>
#include "Maths.h"

class Model
{
	friend class Scene;
public:
	Model(const char* filename);

	Maths::Vec3f Model::vert(int iface, int nthvert);
	Maths::Vec2f Model::uv(int iface, int nthvert);
	Maths::Vec3f Model::normal(int iface, int nthvert);

private:
	std::vector<Maths::Vec3f> verts;
	std::vector<std::vector<Maths::Vec3f>> faces;
	std::vector<Maths::Vec3f> normals;
	std::vector<Maths::Vec2f> uvs;
};

