#pragma once

#include "Manager/ResourceManager.h"

class GameObjectFactory
{
private:
	ResourceManager& m_resourceManager;

public:

	explicit GameObjectFactory(ResourceManager& resourceManager);

	std::shared_ptr<class GameObject> makeGround();

	std::shared_ptr<class GameObject> makePlayer();
};