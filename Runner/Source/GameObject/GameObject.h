#pragma once

#include <memory>

#include "Component/Component.h"
#include "Component/Transform.h"
#include "Component/Model.h"

class GameObject
{
private:

	Transform m_transform;

	std::weak_ptr<Model> m_model;

public:

	Transform& getTransform();

	std::weak_ptr<Model> getModel();

	void setModel(std::weak_ptr<Model> model);

};