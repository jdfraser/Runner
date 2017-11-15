#pragma once

#include "Manager.h"
#include <GL/glew.h>

class ResourceManager final : public Manager
{

private:
	const std::string MODEL_DIR = "Assets/Models/";
	const std::string TEXTURE_DIR = "Assets/Textures/";

	std::vector<std::shared_ptr<class GameObject>> m_gameObjects;

	std::vector<std::shared_ptr<class Component>> m_components;

	std::shared_ptr<class GameObject> m_player;

public:
	virtual void startUp() override;

	virtual void shutDown() override;
	
	virtual void tick(float deltaTime) override;

	void cleanupDestroyedSpawnables();

	std::shared_ptr<class GameObject> makeNewObject();

	template<class T>
	std::shared_ptr<class Component> makeNewComponent();

	std::shared_ptr<class GameObject> makeNewPlayer();

	void loadModelData(const std::shared_ptr<class Model> model, std::string modelName);

	GLuint loadShader(std::string shaderName);

	const std::vector<std::shared_ptr<class GameObject>>& getDrawObjects();

	const std::vector<std::shared_ptr<class GameObject>>& getAllGameObjects();

	const std::shared_ptr<class GameObject> getPlayer();

	static bool isValid(std::shared_ptr<class Spawnable> spawnableObject);
};

template <typename T>
std::shared_ptr<class Component> ResourceManager::makeNewComponent() {
	std::shared_ptr<class Component> component = std::make_shared<T>();

	m_components.push_back(component);

	return component;
}
