#include "FlatShader.h"

vec4 FlatShader::Vertex(int iFace, int nthVert)
{
	vec3 vposition = model->vert(iFace, nthVert);
	vec4 projectionSpace = MVP * embed<4>(vposition);

	// Calculate normal to this face
	vec3 wFace[3];
	for (int i = 0; i < 3; i++)
	{
		vec4 world = M.invert_transpose() * embed<4>(model->vert(iFace, i));
		wFace[i] = proj<3>(world);
	}
	vec3 faceNormal = cross((wFace[1] - wFace[0]), (wFace[2] - wFace[0]));

	vec4 lightDirection = vec4(0, 0, 1, 0);
	lightDirection = M * lightDirection;
	vec3 light = proj<3>(lightDirection);

	faceIntensity = (faceNormal.normalise() * light.normalise()) * 0.8;
	if (faceIntensity < 0)
		faceIntensity = 0;

	return projectionSpace;
}

bool FlatShader::Fragment(vec3 barycentric, vec3 &Color)
{
	Color = vec3(faceIntensity * 255, faceIntensity * 122, faceIntensity * 122);
	return true;
}