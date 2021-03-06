#include "glm/gtc/constants.hpp"

#include "GameObjectFactory.h"
#include "Manager/ResourceManager.h"

#include "GameObject.h"
#include "Player.h"
#include "Ground.h"
#include "Obstacle.h"

#include "Spawnable/Component/Model.h"
#include "Spawnable/Component/InputHandler.h"
#include "Spawnable/Component/Material.h"

GameObjectFactory::GameObjectFactory(ResourceManager& resourceManager) : m_resourceManager(resourceManager) {

}

std::shared_ptr<Ground> GameObjectFactory::makeGround() {
	std::shared_ptr<Material> groundMaterial = m_resourceManager.makeMaterial("Assets/Textures/ground.DDS");
	std::shared_ptr<Material> hedgeMaterial  = m_resourceManager.makeMaterial("Assets/Textures/hedge.DDS");

	std::shared_ptr<Ground> ground = ResourceManager::cast<Ground>(m_resourceManager.make<Ground>());

	std::shared_ptr<Model> groundModel = m_resourceManager.makeModel("Assets/Models/ground.obj", groundMaterial);
	groundModel->setOwner(ground);

	std::shared_ptr<Model> leftHedge = m_resourceManager.makeModel("Assets/Models/hedge.obj", hedgeMaterial);
	leftHedge->setOwner(ground);
	leftHedge->getTransform().setPosition(glm::vec3(-3.0f, 0.0f, 0.0f));
	leftHedge->getTransform().setRotation(glm::vec3(0.0f, glm::pi<float>() / 2.0f, 0.0f));
	leftHedge->getTransform().setScale(glm::vec3(2.0f, 1.0f, 1.0f));

	std::shared_ptr<Model> rightHedge = m_resourceManager.makeModel("Assets/Models/hedge.obj", hedgeMaterial);
	rightHedge->setOwner(ground);
	rightHedge->getTransform().setPosition(glm::vec3(3.0f, 0.0f, 0.0f));
	rightHedge->getTransform().setRotation(glm::vec3(0.0f, glm::pi<float>() / 2.0f, 0.0f));
	rightHedge->getTransform().setScale(glm::vec3(2.0f, 1.0f, 1.0f));

	std::shared_ptr<PhysicsHandler> physicsHandler = ResourceManager::cast<PhysicsHandler>(m_resourceManager.make<PhysicsHandler>());
	physicsHandler->setOwner(ground);

	ground->addComponent(groundModel);
	ground->addComponent(leftHedge);
	ground->addComponent(rightHedge);
	ground->addComponent(physicsHandler);

	physicsHandler->setLocalBounds(groundModel->getBounds());

	ground->setGroundModel(groundModel);

	return ground;
}

std::shared_ptr<Obstacle> GameObjectFactory::makeHedge() {
	std::shared_ptr<Obstacle> hedge = ResourceManager::cast<Obstacle>(m_resourceManager.make<Obstacle>());

	std::shared_ptr<Material> material = m_resourceManager.makeMaterial("Assets/Textures/hedge.DDS");
	std::shared_ptr<Model> model       = m_resourceManager.makeModel("Assets/Models/hedge.obj", material);
	model->setOwner(hedge);
	model->getTransform().setScale(glm::vec3(1.5f, 1.0f, 1.0f));

	std::shared_ptr<PhysicsHandler> physicsHandler = ResourceManager::cast<PhysicsHandler>(m_resourceManager.make<PhysicsHandler>());
	physicsHandler->setOwner(hedge);

	hedge->addComponent(model);
	hedge->addComponent(physicsHandler);
	hedge->setObstacleModel(model);

	physicsHandler->setLocalBounds(hedge->getLocalBounds());

	return hedge;
}

std::shared_ptr<class Obstacle> GameObjectFactory::makeWall() {
	std::shared_ptr<Obstacle> wall = ResourceManager::cast<Obstacle>(m_resourceManager.make<Obstacle>());

	std::shared_ptr<Material> material = m_resourceManager.makeMaterial("Assets/Textures/wall.DDS");
	std::shared_ptr<Model> model = m_resourceManager.makeModel("Assets/Models/wall.obj", material);
	model->setOwner(wall);

	std::shared_ptr<PhysicsHandler> physicsHandler = ResourceManager::cast<PhysicsHandler>(m_resourceManager.make<PhysicsHandler>());
	physicsHandler->setOwner(wall);

	wall->addComponent(model);
	wall->addComponent(physicsHandler);
	wall->setObstacleModel(model);

	physicsHandler->setLocalBounds(wall->getLocalBounds());

	return wall;
}

std::shared_ptr<GameObject> GameObjectFactory::makePlayer() {
	std::shared_ptr<Player> player                 = ResourceManager::cast<Player>(m_resourceManager.makePlayer());
	std::shared_ptr<InputHandler> inputHandler     = ResourceManager::cast<InputHandler>(m_resourceManager.make<InputHandler>());
	std::shared_ptr<PhysicsHandler> physicsHandler = ResourceManager::cast<PhysicsHandler>(m_resourceManager.make<PhysicsHandler>());

	inputHandler->setOwner(player);
	physicsHandler->setOwner(player);

	player->addComponent(inputHandler);
	player->addComponent(physicsHandler);

	physicsHandler->setLocalBounds(getPlayerBounds());
	physicsHandler->setHasPhysics(true);

	return player;
}

Bounds GameObjectFactory::getPlayerBounds() const {
	Bounds playerBounds;
	playerBounds.min = glm::vec3(-0.5f, -0.5f, -0.25f);
	playerBounds.max = glm::vec3(0.5f, 0.5f, 0.25f);

	return playerBounds;
}
