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

	vec3 position;
	vec3 scale;
	vec3 rotation;
};

