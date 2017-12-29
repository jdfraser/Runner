#include "GameObject.h"

#include "Manager/ResourceManager.h"

#include "Spawnable/Component/Component.h"
#include "Spawnable/Component/Model.h"
#include "Spawnable/Component/InputHandler.h"

void GameObject::addBounds(Bounds bounds) {
	m_bounds.max.x = glm::max(m_bounds.max.x, bounds.max.x);
	m_bounds.max.y = glm::max(m_bounds.max.y, bounds.max.y);
	m_bounds.max.z = glm::max(m_bounds.max.z, bounds.max.z);

	m_bounds.min.x = glm::min(m_bounds.min.x, bounds.min.x);
	m_bounds.min.y = glm::min(m_bounds.min.y, bounds.min.y);
	m_bounds.min.z = glm::min(m_bounds.min.z, bounds.min.z);
}

void GameObject::tick(float deltaTime) {
	if (!canTick()) {
		return;
	}

	m_transform.rebuildMatrix();

	for (std::shared_ptr<Component> component : m_components) {
		if (!component->canTick()) {
			continue;
		}

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

Bounds GameObject::getBounds() const {
	return m_bounds;
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

void GameObject::addComponent(std::shared_ptr<Model> model) {
	addBounds(model->getBounds());

	m_components.push_back(ResourceManager::cast<Component>(model));
}
