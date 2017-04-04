#include "FlatShader.h"

Maths::Vec4f FlatShader::Vertex(int iFace, int nthVert)
{
	Maths::Vec3f vposition = model->vert(iFace, nthVert);
	Maths::Vec4f projectionSpace = MVP * Maths::Vec4f(vposition, 1);

	// Calculate normal to this face
	Maths::Vec3f wFace[3];
	for (int i = 0; i < 3; i++)
	{
		Maths::Vec4f world = M.Transpose().Inverse() * Maths::Vec4f(model->vert(iFace, i), 1.f);
		wFace[i] = Maths::Vec3f(world.X, world.Y, world.Z);
	}
	Maths::Vec3f faceNormal = Maths::Cross((wFace[1] - wFace[0]), (wFace[2] - wFace[0]));

	Maths::Vec4f lightDirection = Maths::Vec4f(0, 0, 1, 0);
	lightDirection = M * lightDirection;
	Maths::Vec3f light = Maths::Vec3f(lightDirection.X, lightDirection.Y, lightDirection.Z);

	faceIntensity = Maths::Dot(Maths::Normalize(faceNormal), Maths::Normalize(light)) * 0.8;
	if (faceIntensity < 0)
		faceIntensity = 0;

	return projectionSpace;
}

bool FlatShader::Fragment(Maths::Vec3f barycentric, Maths::Vec3f &Color)
{
	Color = Maths::Vec3f(faceIntensity * 255, faceIntensity * 122, faceIntensity * 122);
	return true;
}