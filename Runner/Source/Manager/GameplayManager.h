#pragma once

#include "Manager.h"
#include "GameObject/GameObjectFactory.h"

class GameplayManager : public Manager
{
private:
	class ResourceManager& m_resourceManager;

	GameObjectFactory m_factory;

public:
	GameplayManager(class ResourceManager& resourceManager);

	~GameplayManager() = default;

	virtual void startUp() override;

	virtual void shutDown() override;

	void tick(float deltaTime);

};