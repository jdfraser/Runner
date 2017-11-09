#include "Common.h"
#include "GameplayManager.h"
#include "GameObject/GameObject.h"

GameplayManager::GameplayManager(class ResourceManager& resourceManager)
	: m_resourceManager(resourceManager),
	m_factory(resourceManager) {

}

void GameplayManager::startUp() {
	std::shared_ptr<GameObject> player = m_factory.makePlayer();
	std::shared_ptr<GameObject> ground = m_factory.makeGround();

	player->getTransform().setPosition(ground->getTransform().getPosition() + glm::vec3(0.0f, 0.5f, 2.0f));
}

void GameplayManager::shutDown() {

}

void GameplayManager::tick(float deltaTime) {
	for (std::shared_ptr<GameObject> gameObject : m_resourceManager.getAllGameObjects()) {
		gameObject->tick(deltaTime);
	}
}
