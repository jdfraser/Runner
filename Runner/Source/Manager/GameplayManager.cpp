#include <glm/gtc/random.hpp>

#include <algorithm>

#include "Common.h"
#include "GameplayManager.h"
#include "GraphicsManager.h"
#include "GameObject/GameObject.h"
#include "Component/Model.h"

GameplayManager::GameplayManager(class ResourceManager& resourceManager, class GraphicsManager& graphicsManager)
	: m_resourceManager(resourceManager),
	  m_graphicsManager(graphicsManager),
	  m_factory(resourceManager) 
{

}

void GameplayManager::startUp() {
	m_player = m_factory.makePlayer();
	m_player->getTransform().setPosition(glm::vec3(0.0f, 0.5f, 0.0f));

	initializeGround();
}

void GameplayManager::shutDown() {

}

void GameplayManager::tick(float deltaTime) {
	destroyUnusedObjects();
	generateGround();
	generateObstacles();
	
	for (std::shared_ptr<GameObject> gameObject : m_resourceManager.findByType<GameObject>()) {
		if (!ResourceManager::isValid(gameObject)) {
			continue;
		}

		gameObject->tick(deltaTime);
	}
}

void GameplayManager::initializeGround() {
	std::shared_ptr<GameObject> ground = m_factory.makeGround();

	glm::vec3 playerPosition = m_player->getPosition();
	ground->setPosition(glm::vec3(playerPosition.x, 0.0f, playerPosition.z));

	m_groundInstances.push_back(ground);

	generateGround();
}

void GameplayManager::generateGround() {
	assert(m_groundInstances.size() > 0);

	std::shared_ptr<GameObject> furthestGround = m_groundInstances.back();

	while (m_groundInstances.size() < MIN_GROUND_INSTANCES) {
		std::shared_ptr<GameObject> ground = m_factory.makeGround();

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
	for (std::shared_ptr<GameObject>& ground : m_groundInstances) {
		if (ground->getPosition().z > m_player->getPosition().z + (ground->getDepth() / 2)) {
			ground->destroy();
			ground.reset();
		}
	}

	for (std::shared_ptr<GameObject>& obstacle : m_obstacles) {
		if (obstacle->getPosition().z > m_player->getPosition().z + (obstacle->getDepth() / 2)) {
			obstacle->destroy();
			obstacle.reset();
		}
	}

	ResourceManager::eraseNullPointers<std::shared_ptr<GameObject>>(m_groundInstances);
	ResourceManager::eraseNullPointers<std::shared_ptr<GameObject>>(m_obstacles);
}

void GameplayManager::generateObstacles() {
	float z = generateObstacleZ();

	if (z < m_player->getPosition().z - MAX_DISTANCE) {
		return;
	}

	float x = generateObstacleX();

	std::shared_ptr<GameObject> obstacle = m_factory.makeHedge();
	obstacle->setPosition(glm::vec3(x, 0.0f, z));

	m_obstacles.push_back(obstacle);
}

float GameplayManager::generateObstacleZ() {
	float minDepth = m_player->getPosition().z - m_graphicsManager.getMaxViewDistance();

	if (m_obstacles.size() > 0) {
		std::shared_ptr<GameObject> furthestObstacle = m_obstacles.back();
		minDepth = glm::min(minDepth, furthestObstacle->getPosition().z - MIN_DISTANCE_BETWEEN_OBSTACLES);
	}

	return minDepth - glm::linearRand(0.0f, 10.0f);
}

float GameplayManager::generateObstacleX() {
	float sign = (glm::linearRand(0.0f, 1.0f) <= chanceToSpawnRight) ? 1.0f : -1.0f;

	chanceToSpawnRight -= sign * SPAWN_CHANCE_INCREMENT;
	chanceToSpawnRight = glm::clamp(chanceToSpawnRight, 0.0f, 1.0f);

	return sign * glm::linearRand(MIN_OBSTACLE_X_OFFSET, MAX_OBSTACLE_X_OFFSET);
}
