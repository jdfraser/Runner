#pragma once

#include "Component/Component.h"
#include "Component/Transform.h"
#include "Component/Model.h"

class GameObject
{
private:

	Transform m_transform;

	Model* m_model;

public:

	Transform& getTransform();

	Model* getModel();

	void setModel(Model* model);

};