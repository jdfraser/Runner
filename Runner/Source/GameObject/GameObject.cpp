#include "GameObject.h"

#include "Component/Component.h"
#include "Component/Model.h"
#include "Component/InputHandler.h"

Transform& GameObject::getTransform() {
	return m_transform;
}

std::weak_ptr<Model> GameObject::getModel() {
	return m_model;
}

void GameObject::setModel(std::weak_ptr<Model> model) {
	m_model = model;

	std::weak_ptr<Component> component = std::dynamic_pointer_cast<Component>(model.lock());

	m_components.push_back(m_inputHandler);
}

std::weak_ptr<InputHandler> GameObject::getInputHandler() {
	return m_inputHandler;
}

void GameObject::setInputHandler(std::weak_ptr<InputHandler> inputHandler) {
	m_inputHandler = inputHandler;
	
	m_components.push_back(m_inputHandler);
}

void GameObject::tick(float deltaTime) {
	for (std::weak_ptr<Component> component : m_components) {
		std::shared_ptr<Component> spComponent = component.lock();
		if (!spComponent) {
			continue;
		}

		spComponent->tick(deltaTime);
	}
}