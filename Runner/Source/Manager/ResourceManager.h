#pragma once

#include "Manager.h"
#include <GL/glew.h>

class ResourceManager final : public Manager
{

private:
	const std::string MODEL_DIR = "Assets/Models/";

	std::vector<std::shared_ptr<class GameObject>> m_gameObjects;

	std::vector<std::shared_ptr<class Component>> m_components;

public:
	virtual void startUp() override;

	virtual void shutDown() override;

	std::shared_ptr<class GameObject> makeNewObject();

	template<class T>
	std::shared_ptr<class Component> makeNewComponent();

	void loadModelData(const std::shared_ptr<class Model> model, std::string modelFile);

	GLuint loadShader(std::string shaderName);
};

template <typename T>
std::shared_ptr<class Component> ResourceManager::makeNewComponent() {
	std::shared_ptr<class Component> component = std::make_shared<T>();

	m_components.push_back(component);

	return component;
}
