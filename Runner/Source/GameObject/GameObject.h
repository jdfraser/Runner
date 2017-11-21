#pragma once

#include "Common.h"
#include "Component/Component.h"
#include "Component/Model.h"
#include "Engine/Transform.h"

class GameObject : public Spawnable
{
private:
	Transform m_transform;

	std::shared_ptr<Model> m_model;

	std::shared_ptr<class InputHandler> m_inputHandler;

	std::vector<std::shared_ptr<Component>> m_components;

public:
	virtual void tick(float deltaTime) override;

	virtual void destroy() final override;

	Transform& getTransform();

	std::shared_ptr<Model> getModel();

	void setModel(std::shared_ptr<Model> model);

	std::shared_ptr<class InputHandler> getInputHandler();

	void setInputHandler(std::shared_ptr<class InputHandler> inputHandler);

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
};