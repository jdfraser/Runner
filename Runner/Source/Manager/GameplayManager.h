#pragma once

#include "Manager.h"
#include "GameObject/GameObjectFactory.h"

class GameplayManager : public Manager
{
private:
	const int MIN_GROUND_INSTANCES = 6;

	class ResourceManager& m_resourceManager;

	GameObjectFactory m_factory;

	std::shared_ptr<GameObject> m_player;

	std::vector<std::shared_ptr<GameObject>> m_groundInstances;

public:
	GameplayManager(class ResourceManager& resourceManager);

	~GameplayManager() = default;

	virtual void startUp() override;

	virtual void shutDown() override;

	virtual void tick(float deltaTime) override;

private:
	void generateGround();
};