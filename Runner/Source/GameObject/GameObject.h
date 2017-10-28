#pragma once

#include <memory>
#include <vector>

#include "Component/Component.h"
#include "Component/Transform.h"

class GameObject
{
private:

	Transform m_transform;

	std::weak_ptr<class Model> m_model;

	std::weak_ptr<class InputHandler> m_inputHandler;

	std::vector<std::weak_ptr<Component>> m_components;

public:
	Transform& getTransform();

	std::weak_ptr<class Model> getModel();

	void setModel(std::weak_ptr<class Model> model);

	std::weak_ptr<class InputHandler> getInputHandler();

	void setInputHandler(std::weak_ptr<class InputHandler> inputHandler);

	void tick(float deltaTime);

};