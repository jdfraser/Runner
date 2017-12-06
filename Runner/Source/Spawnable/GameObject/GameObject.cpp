#include "GameObject.h"

#include "Manager/ResourceManager.h"

#include "Spawnable/Component/Component.h"
#include "Spawnable/Component/Model.h"
#include "Spawnable/Component/InputHandler.h"

void GameObject::tick(float deltaTime) {
	if (!canTick()) {
		return;
	}

	m_transform.rebuildMatrix();

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

std::shared_ptr<InputHandler> GameObject::getInputHandler() {
	return m_inputHandler;
}

std::shared_ptr<PhysicsHandler> GameObject::getPhysicsHandler() {
	return m_physicsHandler;
}

void GameObject::addComponent(std::shared_ptr<Component> component) {
	m_components.push_back(component);
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
