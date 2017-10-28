#include <memory>
#include <iostream>

#include "GameObjectFactory.h"
#include "Manager/ResourceManager.h"
#include "GameObject/GameObject.h"
#include "Component/Model.h"
#include "Component/InputHandler.h"
#include "Graphics/Material.h"

GameObjectFactory::GameObjectFactory(ResourceManager& resourceManager) : m_resourceManager(resourceManager) {

}

std::weak_ptr<GameObject> GameObjectFactory::makeCube() {
	std::weak_ptr<class Material> mat          = m_resourceManager.getNewMaterial();
	std::weak_ptr<class Model> model           = m_resourceManager.getNewModel("", mat);
	std::weak_ptr<class GameObject> gameObject = m_resourceManager.getNewObject();

	model.lock()->setOwner(gameObject);
	gameObject.lock()->setModel(model);

	return gameObject;
}

std::weak_ptr<class GameObject> GameObjectFactory::makePlayer() {
	std::weak_ptr<GameObject> player               = m_resourceManager.getNewObject();
	std::weak_ptr<class InputHandler> inputHandler = m_resourceManager.getNewComponent<InputHandler>();

	inputHandler.lock()->setOwner(player);
	player.lock()->setInputHandler(inputHandler);

	return player;
}
