#include "Model.h"

#include <sstream>
#include <fstream>
#include <iostream>



Model::Model(const char* filename)
{
	std::ifstream in;
	in.open(filename, std::ifstream::in);
	
	if (in.fail())
	{
		auto fa = in.failbit;
		return;
	}
	std::string line;
	while (!in.eof())
	{
		std::getline(in, line);
		std::istringstream iss(line.c_str());
		char trash;
		if (!line.compare(0, 2, "v ")) {
			iss >> trash;
			Maths::Vec3f vertex;
			iss >> vertex.X;
			iss >> vertex.Y;
			iss >> vertex.Z;
			vertex.Z = -vertex.Z;
			verts.push_back(vertex);
		}
		else if (!line.compare(0, 3, "vn "))
		{
			iss >> trash >> trash;
			Maths::Vec3f norm;
			iss >> norm.X;
			iss >> norm.Y;
			iss >> norm.Z;
			normals.push_back(Maths::Normalize(norm));
		}
		else if (!line.compare(0, 3, "vt "))
		{
			iss >> trash >> trash;
			Maths::Vec2f uv;
			iss >> uv.X;
			iss >> uv.Y;
			uvs.push_back(uv);
		}
		else if (!line.compare(0, 2, "f "))
		{
			std::vector<Maths::Vec3f> f;
			Maths::Vec3f vert;
			iss >> trash;
			while (iss >> vert[0] >> trash >> vert[1] >> trash >> vert[2])
			{
				for (int i = 0; i<3; i++) vert[i]--;
				f.push_back(vert);
			}
			faces.push_back(f);
		}
	}
}


Maths::Vec3f Model::vert(int iface, int nthvert) {
	return verts[faces[iface][nthvert][0]];
}

Maths::Vec2f Model::uv(int iface, int nthvert) {
	return uvs[faces[iface][nthvert][1]];
}

Maths::Vec3f Model::normal(int iface, int nthvert) {
	int idx = faces[iface][nthvert][2];
	return normals[idx];
}