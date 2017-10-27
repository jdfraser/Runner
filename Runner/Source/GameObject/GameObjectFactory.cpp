#include <memory>

#include "GameObjectFactory.h"
#include "Manager/ResourceManager.h"
#include "GameObject/GameObject.h"
#include "Component/Model.h"
#include "Graphics/Material.h"

GameObjectFactory::GameObjectFactory(ResourceManager& resourceManager) : m_resourceManager(resourceManager) {

}

std::weak_ptr<GameObject> GameObjectFactory::makeCube() {
	std::weak_ptr<Material> mat          = m_resourceManager.getNewMaterial();
	std::weak_ptr<Model> model           = m_resourceManager.getNewModel("", mat);
	std::weak_ptr<GameObject> gameObject = m_resourceManager.getNewObject();

	gameObject.lock()->setModel(model);

	return gameObject;
}

std::weak_ptr<class GameObject> GameObjectFactory::makePlayer() {
	return m_resourceManager.getNewObject();
}
