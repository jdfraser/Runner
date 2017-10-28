#pragma once

#include <vector>
#include <memory>

#include "Manager.h"

class ResourceManager final : public Manager
{

private:
	std::vector<std::shared_ptr<class GameObject>> m_gameObjects;

	std::vector<std::shared_ptr<class Component>> m_components;

	std::vector<std::shared_ptr<class Model>> m_models;

	std::vector<std::shared_ptr<class Material>> m_materials;

public:
	virtual void startUp() override;

	virtual void shutDown() override;

	std::weak_ptr<class GameObject> getNewObject();

	std::weak_ptr<class Model> getNewModel(const char path[], std::weak_ptr<Material> mat);

	std::weak_ptr<class Material> getNewMaterial();

	template<class T>
	std::weak_ptr<T> getNewComponent();
};

template<class T>
std::weak_ptr<T> ResourceManager::getNewComponent() {
	std::shared_ptr<T> spClass = std::make_shared<T>();

	std::shared_ptr<Component> spComponent = std::dynamic_pointer_cast<Component>(spClass);

	m_components.push_back(spComponent);

	return std::weak_ptr<T>(spClass);
}
