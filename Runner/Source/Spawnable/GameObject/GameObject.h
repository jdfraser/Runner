#pragma once

#include "Util/Common.h"
#include "Spawnable/Component/Component.h"
#include "Spawnable/Component/Model.h"
#include "Spawnable/Component/InputHandler.h"
#include "Spawnable/Component/PhysicsHandler.h"
#include "Engine/Transform.h"

class GameObject : public Spawnable
{
private:
	Transform m_transform;

	std::vector<std::shared_ptr<Component>> m_components;

	std::shared_ptr<Model> m_model;
	std::shared_ptr<InputHandler> m_inputHandler;
	std::shared_ptr<PhysicsHandler> m_physicsHandler;

public:
	virtual void tick(float deltaTime) override;

	virtual void destroy() final override;

	std::shared_ptr<Model> getModel();

	std::shared_ptr<InputHandler> getInputHandler();

	std::shared_ptr<PhysicsHandler> getPhysicsHandler();

	void addComponent(std::shared_ptr<Component> component);

	void addComponent(std::shared_ptr<Model> model);

	void addComponent(std::shared_ptr<InputHandler> inputHandler);

	void addComponent(std::shared_ptr<PhysicsHandler> physicsHandler);

	inline glm::vec3 getPosition() const { return m_transform.getPosition(); }

	inline void setPosition(glm::vec3 position) { m_transform.setPosition(position); }

	inline glm::vec3 getRotation() const { return m_transform.getRotation(); }

	inline void setRotation(glm::vec3 rotation) { m_transform.setRotation(rotation); }

	inline glm::vec3 getScale() const { return m_transform.getScale(); }

	inline void setScale(glm::vec3 scale) { m_transform.setScale(scale); }

	inline glm::vec3 getUpVector() const { return m_transform.getUpVector(); }

	inline glm::vec3 getForwardVector() const { return m_transform.getForwardVector(); }

	inline glm::vec3 getRightVector() const { return m_transform.getRightVector(); }

	inline glm::mat4 getTransformMatrix() const { return m_transform.getMatrix(); }

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
