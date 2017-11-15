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

	generateGround();
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

void GameplayManager::generateGround() {
	std::shared_ptr<GameObject> player = m_resourceManager.getPlayer();
	glm::vec3 playerPos = player->getTransform().getPosition();

	float furthestZ = 0.0f;
	std::vector<std::shared_ptr<GameObject>> groundInFront;
	for (std::shared_ptr<GameObject>& ground : m_groundInstances) {
		glm::vec3 groundPos = ground->getTransform().getPosition();
		if (groundPos.z > playerPos.z) {
			ground->destroy();
			ground.reset();
		} else {
			groundInFront.push_back(ground);
			if (groundPos.z < furthestZ) {
				furthestZ = groundPos.z;
			}
		}
	}

	while (static_cast<int>(groundInFront.size()) < MIN_GROUND_INSTANCES) {
		std::shared_ptr<GameObject> ground = m_factory.makeGround();

		float depth        = ground->getModel()->getBounds().max.z - ground->getModel()->getBounds().min.z;
		glm::vec3 position = glm::vec3(0.0f, 0.0f, furthestZ - depth);

		furthestZ = position.z;
		ground->getTransform().setPosition(position);

		m_groundInstances.push_back(ground);
		groundInFront.push_back(ground);
	}

	m_groundInstances.erase(
		std::remove_if(
			m_groundInstances.begin(), 
			m_groundInstances.end(), 
			[](std::shared_ptr<GameObject>& gameObject) { return gameObject == nullptr; }
		), 
		m_groundInstances.end()
	);
}
