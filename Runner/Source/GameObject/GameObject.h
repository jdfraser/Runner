#pragma once

#include <memory>
#include <vector>

#include "Component/Component.h"
#include "Component/Transform.h"

class GameObject
{
private:

	Transform m_transform;

	std::shared_ptr<class Model> m_model;

	std::shared_ptr<class InputHandler> m_inputHandler;

	std::vector<std::shared_ptr<Component>> m_components;

public:
	Transform& getTransform();

	std::shared_ptr<class Model> getModel();

	void setModel(std::shared_ptr<class Model> model);

	std::shared_ptr<class InputHandler> getInputHandler();

	void setInputHandler(std::shared_ptr<class InputHandler> inputHandler);

	void tick(float deltaTime);

};