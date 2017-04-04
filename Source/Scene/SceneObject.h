#pragma once
#include "Model.h"
#include "Maths.h"
#include "Shader.h"

class SceneObject
{
public:
	SceneObject(Model* model);
	~SceneObject();
	Model* model;
	
	Shader* shader;

	Maths::Vec3f position;
	Maths::Vec3f scale;
	Maths::Vec3f rotation;
};

