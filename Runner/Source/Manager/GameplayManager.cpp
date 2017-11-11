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
	for (std::shared_ptr<GameObject> gameObject : m_resourceManager.getAllGameObjects()) {
		gameObject->tick(deltaTime);
	}

	generateGround();
}

void GameplayManager::generateGround() {
	std::shared_ptr<GameObject> player = m_resourceManager.getPlayer();
	glm::vec3 playerPos = player->getTransform().getPosition();

	float furthestZ = 0.0f;
	std::vector<std::shared_ptr<GameObject>> groundInFront;
	for (std::shared_ptr<GameObject> ground : m_groundInstances) {
		glm::vec3 groundPos = ground->getTransform().getPosition();
		if (groundPos.z > playerPos.z) {
			// TODO: destroy this ground instance
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
}
