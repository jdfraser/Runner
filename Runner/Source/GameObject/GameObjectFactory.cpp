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

	gameObject->addComponent(model);
	model->setOwner(gameObject);

	return gameObject;
}

std::shared_ptr<GameObject> GameObjectFactory::makePlayer() {
	std::shared_ptr<GameObject> player             = ResourceManager::cast<GameObject>(m_resourceManager.makeNewPlayer());
	std::shared_ptr<InputHandler> inputHandler     = ResourceManager::cast<InputHandler>(m_resourceManager.make<InputHandler>());

	inputHandler->setOwner(player);
	player->addComponent(inputHandler);

	return player;
}
