#include "GameObjectFactory.h"
#include "Manager/ResourceManager.h"
#include "GameObject/GameObject.h"
#include "GameObject.h"
#include "Component/Model.h"
#include "Component/InputHandler.h"
#include "Component/Material.h"

GameObjectFactory::GameObjectFactory(ResourceManager& resourceManager) : m_resourceManager(resourceManager) {

}

std::shared_ptr<GameObject> GameObjectFactory::makeGround() {
	std::shared_ptr<GameObject> gameObject = ResourceManager::cast<GameObject>(m_resourceManager.make<GameObject>());

	std::shared_ptr<Model> model = ResourceManager::cast<Model>(m_resourceManager.make<Model>());
	m_resourceManager.loadModelData(model, "ground");

	gameObject->addComponent(model);
	model->setOwner(gameObject);

	return gameObject;
}

std::shared_ptr<GameObject> GameObjectFactory::makeHedge() {
	std::shared_ptr<GameObject> gameObject = ResourceManager::cast<GameObject>(m_resourceManager.make<GameObject>());

	std::shared_ptr<Model> model = ResourceManager::cast<Model>(m_resourceManager.make<Model>());
	m_resourceManager.loadModelData(model, "hedge");

	std::shared_ptr<PhysicsHandler> physicsHandler = ResourceManager::cast<PhysicsHandler>(m_resourceManager.make<PhysicsHandler>());
	physicsHandler->setBounds(model->getBounds());

	model->setOwner(gameObject);
	physicsHandler->setOwner(gameObject);

	gameObject->addComponent(model);
	gameObject->addComponent(physicsHandler);

	return gameObject;
}

std::shared_ptr<GameObject> GameObjectFactory::makePlayer() {
	std::shared_ptr<GameObject> player             = ResourceManager::cast<GameObject>(m_resourceManager.makeNewPlayer());
	std::shared_ptr<InputHandler> inputHandler     = ResourceManager::cast<InputHandler>(m_resourceManager.make<InputHandler>());
	std::shared_ptr<PhysicsHandler> physicsHandler = ResourceManager::cast<PhysicsHandler>(m_resourceManager.make<PhysicsHandler>());
	
	Bounds physicsBounds;
	physicsBounds.min = glm::vec3(-1.0f, -1.0f, -1.0f);
	physicsBounds.max = glm::vec3(1.0f, 1.0f, 1.0f);

	physicsHandler->setBounds(physicsBounds);

	inputHandler->setOwner(player);
	physicsHandler->setOwner(player);

	player->addComponent(inputHandler);
	player->addComponent(physicsHandler);

	return player;
}
