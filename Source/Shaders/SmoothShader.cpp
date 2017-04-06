#include <algorithm>
#include "SmoothShader.h"

vec4 SmoothShader::Vertex(int iFace, int nthVert)
{
	vec3 vposition = model->vert(iFace, nthVert);
	vec4 projectionSpace = MVP * embed<4>(vposition);

	// Light pointing along positive z, flipped to match normals
	vec3 light = vec3(0, 0, -1);

	mat4 normTrans = M.invert_transpose();
	vec3 lookup = model->normal(iFace, nthVert);

	vec4 normal =  normTrans * embed<4>(model->normal(iFace, nthVert), 0.f);
	vec3 norm = proj<3>(normal).normalise();
	
	intensity[nthVert] = std::max(0.0f, norm * light);
	if (norm.x > 0.9999 || norm.y > 0.9999 || norm.z > 0.9999)
	{
		int seven = 7 * 7;
	}
	return projectionSpace;
}

bool SmoothShader::Fragment(vec3 barycentric, vec3 &Colour)
{
	float pixelIntensity = intensity * barycentric;
	Colour = vec3(255, 122, 122) * pixelIntensity;
	return true;
}
