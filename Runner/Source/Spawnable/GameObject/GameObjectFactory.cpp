#include "glm/gtc/constants.hpp"

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

	std::shared_ptr<Model> groundModel = ResourceManager::cast<Model>(m_resourceManager.make<Model>());
	m_resourceManager.loadModelData(groundModel, "ground");
	groundModel->setOwner(ground);

	std::shared_ptr<Model> leftHedge = ResourceManager::cast<Model>(m_resourceManager.make<Model>());
	m_resourceManager.loadModelData(leftHedge, "hedge");
	leftHedge->setOwner(ground);
	leftHedge->getTransform().setPosition(glm::vec3(-3.0f, 0.0f, 0.0f));
	leftHedge->getTransform().setRotation(glm::vec3(0.0f, glm::pi<float>() / 2.0f, 0.0f));
	leftHedge->getTransform().setScale(glm::vec3(2.0f, 1.0f, 1.0f));

	std::shared_ptr<Model> rightHedge = ResourceManager::cast<Model>(m_resourceManager.make<Model>());
	m_resourceManager.loadModelData(rightHedge, "hedge");
	rightHedge->setOwner(ground);
	rightHedge->getTransform().setPosition(glm::vec3(3.0f, 0.0f, 0.0f));
	rightHedge->getTransform().setRotation(glm::vec3(0.0f, glm::pi<float>() / 2.0f, 0.0f));
	rightHedge->getTransform().setScale(glm::vec3(2.0f, 1.0f, 1.0f));

	ground->addComponent(groundModel);
	ground->addComponent(leftHedge);
	ground->addComponent(rightHedge);
	ground->setGroundModel(groundModel);

	return ground;
}

std::shared_ptr<Obstacle> GameObjectFactory::makeHedge() {
	std::shared_ptr<Obstacle> obstacle = ResourceManager::cast<Obstacle>(m_resourceManager.make<Obstacle>());

	std::shared_ptr<Model> model = ResourceManager::cast<Model>(m_resourceManager.make<Model>());
	m_resourceManager.loadModelData(model, "hedge");
	model->setOwner(obstacle);
	model->getTransform().setScale(glm::vec3(1.5f, 1.0f, 1.0f));

	std::shared_ptr<PhysicsHandler> physicsHandler = ResourceManager::cast<PhysicsHandler>(m_resourceManager.make<PhysicsHandler>());
	physicsHandler->setOwner(obstacle);

	obstacle->addComponent(model);
	obstacle->addComponent(physicsHandler);
	obstacle->setObstacleModel(model);

	physicsHandler->setLocalBounds(obstacle->getBounds());

	return obstacle;
}

std::shared_ptr<GameObject> GameObjectFactory::makePlayer() {
	std::shared_ptr<GameObject> player             = ResourceManager::cast<GameObject>(m_resourceManager.makeNewPlayer());
	std::shared_ptr<InputHandler> inputHandler     = ResourceManager::cast<InputHandler>(m_resourceManager.make<InputHandler>());
	std::shared_ptr<PhysicsHandler> physicsHandler = ResourceManager::cast<PhysicsHandler>(m_resourceManager.make<PhysicsHandler>());

	inputHandler->setOwner(player);
	physicsHandler->setOwner(player);

	player->addComponent(inputHandler);
	player->addComponent(physicsHandler);

	physicsHandler->setLocalBounds(getPlayerBounds());

	return player;
}

Bounds GameObjectFactory::getPlayerBounds() const {
	Bounds playerBounds;
	playerBounds.min = glm::vec3(-0.5f, -1.0f, -0.25f);
	playerBounds.max = glm::vec3(0.5f, 1.0f, 0.25f);

	return playerBounds;
}
