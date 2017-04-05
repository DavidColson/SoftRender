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
			vec3 vertex;
			iss >> vertex.x;
			iss >> vertex.y;
			iss >> vertex.z;
			vertex.z = -vertex.z;
			verts.push_back(vertex);
		}
		else if (!line.compare(0, 3, "vn "))
		{
			iss >> trash >> trash;
			vec3 norm;
			iss >> norm.x;
			iss >> norm.y;
			iss >> norm.z;
			normals.push_back(norm.normalise());
		}
		else if (!line.compare(0, 3, "vt "))
		{
			iss >> trash >> trash;
			vec2 uv;
			iss >> uv.x;
			iss >> uv.y;
			uvs.push_back(uv);
		}
		else if (!line.compare(0, 2, "f "))
		{
			std::vector<vec3> f;
			vec3 vert;
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


vec3 Model::vert(int iface, int nthvert) {
	return verts[faces[iface][nthvert][0]];
}

vec2 Model::uv(int iface, int nthvert) {
	return uvs[faces[iface][nthvert][1]];
}

vec3 Model::normal(int iface, int nthvert) {
	int idx = faces[iface][nthvert][2];
	return normals[idx];
}