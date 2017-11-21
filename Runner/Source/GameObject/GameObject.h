#pragma once

#include "Common.h"
#include "Component/Component.h"
#include "Component/Model.h"
#include "Component/InputHandler.h"
#include "Component/PhysicsHandler.h"
#include "Engine/Transform.h"

class GameObject : public Spawnable
{
private:
	Transform m_transform;

	std::vector<std::shared_ptr<Component>> m_components;

public:
	virtual void tick(float deltaTime) override;

	virtual void destroy() final override;

	Transform& getTransform();

	std::shared_ptr<Model> getModel();

	std::shared_ptr<InputHandler> getInputHandler();

	std::shared_ptr<PhysicsHandler> getPhysicsHandler();

	void addComponent(std::shared_ptr<Component> component);

	inline glm::vec3 getPosition() { return getTransform().getPosition(); }

	inline void setPosition(glm::vec3 position) { getTransform().setPosition(position); }

	inline glm::vec3 getRotation() { return getTransform().getRotation(); }

	inline void setRotation(glm::vec3 rotation) { getTransform().setRotation(rotation); }

	inline glm::vec3 getScale() { return getTransform().getScale(); }

	inline void setScale(glm::vec3 scale) { getTransform().setScale(scale); }

	inline glm::mat4 getTransformMatrix() { return getTransform().getMatrix(); }

	inline float getWidth() { return getModel()->getBounds().getWidth(); }

	inline float getHeight() { return getModel()->getBounds().getHeight(); }

	inline float getDepth() { return getModel()->getBounds().getDepth(); }

	template<class T>
	const std::vector<std::shared_ptr<Component>> findComponentsByType();
};

template<class T>
const std::vector<std::shared_ptr<Component>> GameObject::findComponentsByType() {
	std::vector<std::shared_ptr<Component>> results;

	for (std::shared_ptr<Component> object : m_components) {
		std::shared_ptr<T> found = ResourceManager::cast<T>(object);
		if (found) {
			results.push_back(object);
		}
	}

	return results;
}
