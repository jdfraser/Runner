#pragma once

#include "Manager.h"
#include <GL/glew.h>

class ResourceManager final : public Manager
{

private:
	const char* MATERIAL_DIR = "Assets/Models/";

	std::vector<std::shared_ptr<class Spawnable>> m_spawnedObjects;

	std::shared_ptr<class GameObject> m_player;

	void loadModelData(std::shared_ptr<class Model> model, std::string path);

	void loadMaterialData(std::shared_ptr<class Material> material, std::string texturePath, std::string shaderName);

public:
	virtual void startUp() override;

	virtual void shutDown() override;
	
	virtual void tick(float deltaTime) override;

	void removeDestroyed();

	template<class T>
	std::shared_ptr<Spawnable> make();

	std::shared_ptr<class GameObject> makePlayer();

	std::shared_ptr<class Model> makeModel(std::string path, std::shared_ptr<class Material> material);

	std::shared_ptr<class Material> makeMaterial(std::string path, std::string shaderName = "default");

	GLuint loadShader(std::string shaderName);

	std::shared_ptr<class GameObject> getPlayer();

	template<class T>
	const std::vector<std::shared_ptr<T>> findByType() const;

	static bool isValid(std::shared_ptr<class Spawnable> spawnableObject);

	template<class To, class From>
	static std::shared_ptr<To> cast(std::shared_ptr<From> from);

	template<class T>
	static void eraseNullPointers(std::vector<T>& pointers);
};

template<class T>
const std::vector<std::shared_ptr<T>> ResourceManager::findByType() const {
	std::vector<std::shared_ptr<T>> results;

	for (std::shared_ptr<Spawnable> object : m_spawnedObjects) {
		std::shared_ptr<T> found = cast<T>(object);
		if (found) {
			results.push_back(found);
		}
	}

	return results;
}

template<class T>
std::shared_ptr<class Spawnable> ResourceManager::make() {
	std::shared_ptr<class Spawnable> spawnable = std::make_shared<T>();
	m_spawnedObjects.push_back(spawnable);

	return spawnable;
}

template<typename To, typename From>
std::shared_ptr<To> ResourceManager::cast(std::shared_ptr<From> from) {
	return std::dynamic_pointer_cast<To>(from);
}

template<class T>
void ResourceManager::eraseNullPointers(std::vector<T>& pointers) {
	pointers.erase(
		std::remove_if(
			pointers.begin(),
			pointers.end(),
			[](T& pointer) { return pointer == nullptr; }
		),
		pointers.end()
	);
}
