#include "FlatShader.h"

vec4 FlatShader::Vertex(int iFace, int nthVert)
{
	vec3 vposition = model->vert(iFace, nthVert);
	vec4 projectionSpace = MVP * embed<4>(vposition);

	// Calculate normal to this face
	vec3 wFace[3];
	for (int i = 0; i < 3; i++)
	{
		wFace[i] = model->vert(iFace, i);
	}
	vec3 faceNormal = cross((wFace[1] - wFace[0]), (wFace[2] - wFace[0]));
	faceNormal = proj<3>(M.invert_transpose() * embed<4>(faceNormal, 0.f));

	vec3 light = vec3(0, 0, 1);

	faceIntensity = (faceNormal.normalise() * light) * 1.0;
	if (faceIntensity < 0)
		faceIntensity = 0;

	return projectionSpace;
}

bool FlatShader::Fragment(vec3 barycentric, vec3 &Color)
{
	Color = vec3(faceIntensity * 255, faceIntensity * 255, faceIntensity * 255);
	return true;
}