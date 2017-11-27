#include "GameObject.h"

#include "Manager/ResourceManager.h"

#include "Spawnable/Component/Component.h"
#include "Spawnable/Component/Model.h"
#include "Spawnable/Component/InputHandler.h"

Transform& GameObject::getTransform() {
	return m_transform;
}

std::shared_ptr<Model> GameObject::getModel() {
	return m_model;
}

std::shared_ptr<InputHandler> GameObject::getInputHandler() {
	return m_inputHandler;
}

std::shared_ptr<PhysicsHandler> GameObject::getPhysicsHandler() {
	return m_physicsHandler;
}

void GameObject::addComponent(std::shared_ptr<Component> component) {
	m_components.push_back(component);
}

void GameObject::addComponent(std::shared_ptr<Model> model) {
	assert(m_model == nullptr);

	m_model = model;
	m_components.push_back(ResourceManager::cast<Component>(model));
}

void GameObject::addComponent(std::shared_ptr<InputHandler> inputHandler) {
	assert(m_inputHandler == nullptr);

	m_inputHandler = inputHandler;
	m_components.push_back(ResourceManager::cast<Component>(inputHandler));
}

void GameObject::addComponent(std::shared_ptr<PhysicsHandler> physicsHandler) {
	assert(m_physicsHandler == nullptr);

	m_physicsHandler = physicsHandler;
	m_components.push_back(ResourceManager::cast<Component>(physicsHandler));
}

void GameObject::tick(float deltaTime) {
	if (!canTick()) {
		return;
	}

	for (std::shared_ptr<Component> component : m_components) {
		component->tick(deltaTime);
	}
}

void GameObject::destroy() {
	Spawnable::destroy();

	for (std::shared_ptr<Component> component : m_components) {
		component->destroy();
		component.reset();
	}
}
