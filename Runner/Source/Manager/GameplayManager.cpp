#include <glm/gtc/random.hpp>

#include <algorithm>

#include "Util/Common.h"
#include "GameplayManager.h"
#include "GraphicsManager.h"
#include "EventManager.h"
#include "Spawnable/GameObject/GameObject.h"
#include "Spawnable/GameObject/Ground.h"
#include "Spawnable/GameObject/Obstacle.h"
#include "Spawnable/Component/Model.h"

GameplayManager::GameplayManager(
	ResourceManager& resourceManager, 
	GraphicsManager& graphicsManager, 
	EventManager& eventManager
) : m_resourceManager(resourceManager),
	m_graphicsManager(graphicsManager),
	m_eventManager(eventManager),
	m_factory(resourceManager) 
{

}

void GameplayManager::startUp() {
	m_player = m_factory.makePlayer();
	m_graphicsManager.setCamera(m_player);

	initializePlayer();
	initializeGround();
}

void GameplayManager::shutDown() {

}

void GameplayManager::tick(float deltaTime) {
	destroyUnusedObjects();
	generateGround();
	generateObstacles();
	handleCollisions();
	
	for (std::shared_ptr<GameObject> gameObject : m_resourceManager.findByType<GameObject>()) {
		if (!ResourceManager::isValid(gameObject)) {
			continue;
		}

		gameObject->tick(deltaTime);
	}
}

void GameplayManager::handleCollisions() {
	while (m_eventManager.hasCollisionEvent()) {
		CollisionEvent event = m_eventManager.getNextCollisionEvent();
		std::shared_ptr<GameObject> ownerA = event.firstCollider->getOwner();
		std::shared_ptr<GameObject> ownerB = event.secondCollider->getOwner();

		if (ownerA == m_resourceManager.getPlayer() || ownerB == m_resourceManager.getPlayer()) {
			resetLevel();
		}
	}
}

void GameplayManager::initializeGround() {
	std::shared_ptr<Ground> ground = m_factory.makeGround();

	glm::vec3 playerPosition = m_player->getPosition();
	ground->setPosition(glm::vec3(playerPosition.x, 0.0f, playerPosition.z));

	m_groundInstances.push_back(ground);

	generateGround();
}

void GameplayManager::initializePlayer() {
	m_player->setPosition(glm::vec3(0.0f, 0.5f, 0.0f));
}

void GameplayManager::generateGround() {
	assert(m_groundInstances.size() > 0);

	std::shared_ptr<Ground> furthestGround = m_groundInstances.back();

	while (m_groundInstances.size() < MIN_GROUND_INSTANCES) {
		std::shared_ptr<Ground> ground = m_factory.makeGround();

		ground->setPosition(
			glm::vec3(
				0.0f, 
				0.0f, 
				furthestGround->getPosition().z - furthestGround->getDepth()
			)
		);

		furthestGround = ground;

		m_groundInstances.push_back(ground);
	}
}

void GameplayManager::destroyUnusedObjects() {
	for (std::shared_ptr<Ground>& ground : m_groundInstances) {
		if (ground->getPosition().z > m_player->getPosition().z + (ground->getDepth() / 2)) {
			ground->destroy();
			ground.reset();
		}
	}

	for (std::shared_ptr<Obstacle>& obstacle : m_obstacles) {
		if (obstacle->getPosition().z > m_player->getPosition().z + (obstacle->getDepth() / 2)) {
			obstacle->destroy();
			obstacle.reset();
		}
	}

	ResourceManager::eraseNullPointers<std::shared_ptr<Ground>>(m_groundInstances);
	ResourceManager::eraseNullPointers<std::shared_ptr<Obstacle>>(m_obstacles);
}

void GameplayManager::generateObstacles() {
	float z = generateObstacleZ();

	if (z < m_player->getPosition().z - MAX_DISTANCE) {
		return;
	}

	float x = generateObstacleX();

	std::shared_ptr<Obstacle> obstacle = m_factory.makeHedge();
	obstacle->setPosition(glm::vec3(x, 0.0f, z));

	m_obstacles.push_back(obstacle);
}

float GameplayManager::generateObstacleZ() {
	float minDepth = m_player->getPosition().z - m_graphicsManager.getMaxViewDistance();

	if (m_obstacles.size() > 0) {
		std::shared_ptr<Obstacle> furthestObstacle = m_obstacles.back();
		minDepth = glm::min(minDepth, furthestObstacle->getPosition().z - MIN_DISTANCE_BETWEEN_OBSTACLES);
	}

	return minDepth - glm::linearRand(0.0f, 10.0f);
}

float GameplayManager::generateObstacleX() {
	float sign = (glm::linearRand(0.0f, 1.0f) <= chanceToSpawnRight) ? 1.0f : -1.0f;

	chanceToSpawnRight -= sign * SPAWN_CHANCE_INCREMENT;
	chanceToSpawnRight = glm::clamp(chanceToSpawnRight, 0.0f, 1.0f);

	return sign * OBSTACLE_X_OFFSET;
}

void GameplayManager::resetLevel() {
	destroyAllObjects();
	initializePlayer();
	initializeGround();
}

void GameplayManager::destroyAllObjects() {
	for (std::shared_ptr<Ground> ground : m_groundInstances) {
		ground->destroy();
	}

	m_groundInstances.clear();

	for (std::shared_ptr<Obstacle> obstacle : m_obstacles) {
		obstacle->destroy();
	}

	m_obstacles.clear();
}
