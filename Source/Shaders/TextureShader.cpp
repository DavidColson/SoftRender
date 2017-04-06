#include <algorithm>
#include "TextureShader.h"

vec4 TextureShader::Vertex(int iFace, int nthVert)
{
	uvs.setcol(nthVert, model->uv(iFace, nthVert));
	vec3 vposition = model->vert(iFace, nthVert);
	vec4 projectionSpace = MVP * embed<4>(vposition);

	vec3 light = vec3(0, 0, 1);

	mat4 normTrans = M.invert_transpose();
	vec4 normal = normTrans * embed<4>(model->normal(iFace, nthVert), 0.f);
	vec3 norm = proj<3>(normal);
	intensity[nthVert] = std::max(0.2f, norm.normalise() * light.normalise());

	return projectionSpace;
}

bool TextureShader::Fragment(vec3 barycentric, vec3 &Colour)
{
	float pixelIntensity = intensity * barycentric;
	vec2 uv = uvs*barycentric;
	Colour = diffuse->GetPixel(uv.x * diffuse->Width(), uv.y * diffuse->Height()) * pixelIntensity;
	return true;
}
