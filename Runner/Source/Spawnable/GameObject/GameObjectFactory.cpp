#include "GameObjectFactory.h"
#include "Manager/ResourceManager.h"

#include "GameObject.h"
#include "Ground.h"
#include "Obstacle.h"

#include "Spawnable/Component/Model.h"
#include "Spawnable/Component/InputHandler.h"
#include "Spawnable/Component/Material.h"

GameObjectFactory::GameObjectFactory(ResourceManager& resourceManager) : m_resourceManager(resourceManager) {

}

std::shared_ptr<Ground> GameObjectFactory::makeGround() {
	std::shared_ptr<Ground> ground = ResourceManager::cast<Ground>(m_resourceManager.make<Ground>());

	std::shared_ptr<Model> model = ResourceManager::cast<Model>(m_resourceManager.make<Model>());
	m_resourceManager.loadModelData(model, "ground");
	model->setOwner(ground);

	ground->addComponent(model);
	ground->setGroundModel(model);

	return ground;
}

std::shared_ptr<Obstacle> GameObjectFactory::makeHedge() {
	std::shared_ptr<Obstacle> obstacle = ResourceManager::cast<Obstacle>(m_resourceManager.make<Obstacle>());

	std::shared_ptr<Model> model = ResourceManager::cast<Model>(m_resourceManager.make<Model>());
	m_resourceManager.loadModelData(model, "hedge");

	std::shared_ptr<PhysicsHandler> physicsHandler = ResourceManager::cast<PhysicsHandler>(m_resourceManager.make<PhysicsHandler>());

	model->setOwner(obstacle);
	physicsHandler->setOwner(obstacle);

	obstacle->addComponent(model);
	obstacle->addComponent(physicsHandler);
	obstacle->setObstacleModel(model);

	return obstacle;
}

std::shared_ptr<GameObject> GameObjectFactory::makePlayer() {
	std::shared_ptr<GameObject> player             = ResourceManager::cast<GameObject>(m_resourceManager.makeNewPlayer());
	std::shared_ptr<InputHandler> inputHandler     = ResourceManager::cast<InputHandler>(m_resourceManager.make<InputHandler>());
	std::shared_ptr<PhysicsHandler> physicsHandler = ResourceManager::cast<PhysicsHandler>(m_resourceManager.make<PhysicsHandler>());
	
	Bounds physicsBounds;
	physicsBounds.min = glm::vec3(-0.25f, -1.0f, -0.25f);
	physicsBounds.max = glm::vec3(0.25f, 1.0f, 0.25f);

	inputHandler->setOwner(player);
	physicsHandler->setOwner(player);

	player->addComponent(inputHandler);
	player->addComponent(physicsHandler);

	return player;
}
