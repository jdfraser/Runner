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
	std::shared_ptr<GameObject> gameObject = std::dynamic_pointer_cast<GameObject>(m_resourceManager.makeNewObject());

	std::shared_ptr<Model> model = std::dynamic_pointer_cast<Model>(m_resourceManager.makeNewComponent<Model>());
	m_resourceManager.loadModelData(model, "ground");

	gameObject->setModel(model);
	model->setOwner(gameObject);

	return gameObject;
}

std::shared_ptr<GameObject> GameObjectFactory::makeHedge() {
	std::shared_ptr<GameObject> gameObject = std::dynamic_pointer_cast<GameObject>(m_resourceManager.makeNewObject());

	std::shared_ptr<Model> model = std::dynamic_pointer_cast<Model>(m_resourceManager.makeNewComponent<Model>());
	m_resourceManager.loadModelData(model, "hedge");

	gameObject->setModel(model);
	model->setOwner(gameObject);

	return gameObject;
}

std::shared_ptr<GameObject> GameObjectFactory::makePlayer() {
	std::shared_ptr<GameObject> player = std::dynamic_pointer_cast<GameObject>(m_resourceManager.makeNewPlayer());
	std::shared_ptr<InputHandler> inputHandler = std::dynamic_pointer_cast<InputHandler>(m_resourceManager.makeNewComponent<InputHandler>());

	inputHandler->setOwner(player);
	player->setInputHandler(inputHandler);

	return player;
}
