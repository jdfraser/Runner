#include "GameObjectFactory.h"
#include "Manager/ResourceManager.h"
#include "GameObject/GameObject.h"
#include "Component/Model.h"
#include "Component/InputHandler.h"
#include "Component/Material.h"

GameObjectFactory::GameObjectFactory(ResourceManager& resourceManager) : m_resourceManager(resourceManager) {

}

std::shared_ptr<GameObject> GameObjectFactory::makeCube() {
	std::shared_ptr<GameObject> gameObject = std::dynamic_pointer_cast<GameObject>(m_resourceManager.makeNewObject());

	std::shared_ptr<Material> material = std::dynamic_pointer_cast<Material>(m_resourceManager.makeNewComponent<Material>());
	m_resourceManager.loadMaterialData(material);

	std::shared_ptr<Model> model = std::dynamic_pointer_cast<Model>(m_resourceManager.makeNewComponent<Model>());
	model->setMaterial(material);
	model->setOwner(gameObject);

	m_resourceManager.loadModelData(model);

	gameObject->setModel(model);

	return gameObject;
}

std::shared_ptr<class GameObject> GameObjectFactory::makePlayer() {
	std::shared_ptr<GameObject> player               = std::dynamic_pointer_cast<GameObject>(m_resourceManager.makeNewObject());
	std::shared_ptr<class InputHandler> inputHandler = std::dynamic_pointer_cast<InputHandler>(m_resourceManager.makeNewComponent<InputHandler>());

	inputHandler->setOwner(player);
	player->setInputHandler(inputHandler);

	return player;
}
