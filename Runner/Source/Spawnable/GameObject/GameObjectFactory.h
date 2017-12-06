#pragma once

#include "Manager/ResourceManager.h"

class GameObjectFactory
{
private:
	ResourceManager& m_resourceManager;

public:
	GameObjectFactory(ResourceManager& resourceManager);

	std::shared_ptr<class Ground> makeGround();

	std::shared_ptr<class Obstacle> makeHedge();

	std::shared_ptr<class GameObject> makePlayer();
};