#include "SceneObject.h"



SceneObject::SceneObject(Model* withModel)
{
	model = withModel;
}


SceneObject::~SceneObject()
{
	// Free model memory
	delete model;
}
