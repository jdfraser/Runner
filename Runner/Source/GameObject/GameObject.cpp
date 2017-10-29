#include "GameObject.h"

#include "Component/Component.h"
#include "Component/Model.h"
#include "Component/InputHandler.h"

Transform& GameObject::getTransform() {
	return m_transform;
}

std::shared_ptr<Model> GameObject::getModel() {
	return m_model;
}

void GameObject::setModel(std::shared_ptr<Model> model) {
	m_model = model;

	m_components.push_back(m_model);
}

std::shared_ptr<InputHandler> GameObject::getInputHandler() {
	return m_inputHandler;
}

void GameObject::setInputHandler(std::shared_ptr<InputHandler> inputHandler) {
	m_inputHandler = inputHandler;
	
	m_components.push_back(m_inputHandler);
}

void GameObject::tick(float deltaTime) {
	for (std::shared_ptr<Component> component : m_components) {
		component->tick(deltaTime);
	}
}