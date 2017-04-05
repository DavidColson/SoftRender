#include <algorithm>
#include "SmoothShader.h"

vec4 SmoothShader::Vertex(int iFace, int nthVert)
{
	vec3 vposition = model->vert(iFace, nthVert);
	vec4 projectionSpace = MVP * embed<4>(vposition);

	vec4 lightDirection = vec4(0, 0, 1, 0);
	lightDirection = M * lightDirection;
	vec3 light = proj<3>(lightDirection);

	mat4 normTrans = M.invert_transpose();
	vec4 normal =  normTrans * embed<4>(model->normal(iFace, nthVert), 0.f);
	vec3 norm = proj<3>(normal);
	norm.normalise();
	intensity[nthVert] = std::max(0.0f, norm * light);

	return projectionSpace;
}

bool SmoothShader::Fragment(vec3 barycentric, vec3 &Colour)
{
	float pixelIntensity = intensity * barycentric;
	Colour = vec3(255, 122, 122) * pixelIntensity;
	return true;
}
