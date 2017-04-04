#include <algorithm>
#include "SmoothShader.h"

Maths::Vec4f SmoothShader::Vertex(int iFace, int nthVert)
{
	Maths::Vec3f vposition = model->vert(iFace, nthVert);
	Maths::Vec4f projectionSpace = MVP * Maths::Vec4f(vposition, 1);

	Maths::Vec4f lightDirection = Maths::Vec4f(0, 0, 1, 0);
	lightDirection = M * lightDirection;
	Maths::Vec3f light = Maths::Vec3f(lightDirection.X, lightDirection.Y, lightDirection.Z);

	Maths::Mat4f normTrans = M.Transpose().Inverse();
	Maths::Vec4f normal =  normTrans * Maths::Vec4f(model->normal(iFace, nthVert), 0);
	Maths::Vec3f norm = Maths::Vec3f(normal.X, normal.Y, normal.Z);
	norm = Maths::Normalize(norm);
	intensity[nthVert] = std::max(0.0f, Maths::Dot(norm, Maths::Normalize(light)));

	return projectionSpace;
}

bool SmoothShader::Fragment(Maths::Vec3f barycentric, Maths::Vec3f &Colour)
{
	float pixelIntensity = Maths::Dot(intensity, barycentric);
	Colour = Maths::Vec3f(255, 122, 122) * pixelIntensity;
	return true;
}
