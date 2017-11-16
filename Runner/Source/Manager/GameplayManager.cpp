#include <algorithm>

#include "Common.h"
#include "GameplayManager.h"
#include "GameObject/GameObject.h"
#include "Component/Model.h"

GameplayManager::GameplayManager(class ResourceManager& resourceManager)
	: m_resourceManager(resourceManager),
	m_factory(resourceManager) {

}

void GameplayManager::startUp() {
	m_player = m_factory.makePlayer();
	m_player->getTransform().setPosition(glm::vec3(0.0f, 0.5f, 0.0f));

	std::shared_ptr<GameObject> hedge = m_factory.makeHedge();
	hedge->getTransform().setPosition(m_player->getTransform().getPosition() + glm::vec3(1.0f, -0.5f, -10.0f));

	initializeGround();
}

void GameplayManager::shutDown() {

}

void GameplayManager::tick(float deltaTime) {
	generateGround();
	
	for (std::shared_ptr<GameObject> gameObject : m_resourceManager.getAllGameObjects()) {
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
	std::shared_ptr<GameObject> player = m_resourceManager.getPlayer();
	glm::vec3 playerPos = player->getPosition();

	for (std::shared_ptr<GameObject>& ground : m_groundInstances) {
		if (ground->getPosition().z > playerPos.z + ground->getDepth() / 2) {
			// Ground is far enough behind the player that it can't be seen
			ground->destroy();
			ground.reset();
		}
	}

	ResourceManager::eraseNullPointers<GameObject>(m_groundInstances);

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
