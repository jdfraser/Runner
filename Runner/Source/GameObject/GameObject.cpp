#include "GameObject.h"

#include "Manager/ResourceManager.h"

#include "Component/Component.h"
#include "Component/Model.h"
#include "Component/InputHandler.h"

Transform& GameObject::getTransform() {
	return m_transform;
}

std::shared_ptr<Model> GameObject::getModel() {
	std::vector<std::shared_ptr<Component>> models = findComponentsByType<Model>();
	
	if (models.size() == 0) {
		return std::shared_ptr<Model>();
	}

	// TODO: start handling multiple models
	return ResourceManager::cast<Model>(models[0]);
}

std::shared_ptr<InputHandler> GameObject::getInputHandler() {
	std::vector <std::shared_ptr<Component>> inputHandlers = findComponentsByType<InputHandler>();

	if (inputHandlers.size() == 0) {
		return std::shared_ptr<InputHandler>();
	}

	return ResourceManager::cast<InputHandler>(inputHandlers[0]);
}

std::shared_ptr<class PhysicsHandler> GameObject::getPhysicsHandler() {
	std::vector <std::shared_ptr<Component>> physicsHandlers = findComponentsByType<PhysicsHandler>();

	if (physicsHandlers.size() == 0) {
		return std::shared_ptr<PhysicsHandler>();
	}

	return ResourceManager::cast<PhysicsHandler>(physicsHandlers[0]);
}

void GameObject::addComponent(std::shared_ptr<Component> component) {
	m_components.push_back(component);

	assert(findComponentsByType<Model>().size() <= 1);
	assert(findComponentsByType<InputHandler>().size() <= 1);
	assert(findComponentsByType<PhysicsHandler>().size() <= 1);
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
