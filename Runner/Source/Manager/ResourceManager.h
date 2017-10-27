#pragma once

#include <vector>
#include <memory>

#include "Manager.h"

class ResourceManager final : public Manager
{

private:
	std::vector<std::shared_ptr<class GameObject>> m_gameObjects;

	std::vector<std::shared_ptr<class Model>> m_models;

	std::vector<std::shared_ptr<class Material>> m_materials;

public:
	virtual void startUp() override;

	virtual void shutDown() override;

	std::weak_ptr<class GameObject> getNewObject();

	std::weak_ptr<class Model> getNewModel(const char path[], std::weak_ptr<Material> mat);

	std::weak_ptr<class Material> getNewMaterial();
};