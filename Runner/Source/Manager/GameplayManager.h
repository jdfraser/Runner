#pragma once

#include "Manager.h"
#include "Spawnable/GameObject/GameObjectFactory.h"

class GameplayManager : public Manager
{
private:
	const uint32_t MIN_GROUND_INSTANCES = 6;

	const float MIN_DISTANCE_BETWEEN_OBSTACLES = 5.0f;
	const float MAX_DISTANCE = 20.0f;
	const float MIN_OBSTACLE_X_OFFSET = 0.5f;
	const float MAX_OBSTACLE_X_OFFSET = 2.0f;

	const float SPAWN_CHANCE_INCREMENT = 0.25f;

	float chanceToSpawnRight = 0.50f;

	class ResourceManager& m_resourceManager;
	class GraphicsManager& m_graphicsManager;
	class EventManager& m_eventManager;

	GameObjectFactory m_factory;

	std::shared_ptr<GameObject> m_player;

	std::vector<std::shared_ptr<GameObject>> m_groundInstances;

	std::vector<std::shared_ptr<GameObject>> m_obstacles;

public:
	GameplayManager(
		class ResourceManager& resourceManager, 
		class GraphicsManager& graphicsManager, 
		class EventManager& eventManager
	);

	~GameplayManager() = default;

	virtual void startUp() override;

	virtual void shutDown() override;

	virtual void tick(float deltaTime) override;

private:
	void handleCollisions();
	
	void initializeGround();

	void generateGround();

	void destroyUnusedObjects();

	void generateObstacles();

	float generateObstacleZ();

	float generateObstacleX();
};