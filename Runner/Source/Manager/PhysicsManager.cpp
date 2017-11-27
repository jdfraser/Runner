#include "PhysicsManager.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "Spawnable/GameObject/GameObject.h"
#include "Spawnable/Component/PhysicsHandler.h"

PhysicsManager::PhysicsManager(ResourceManager& resourceManager, EventManager& eventManager)
	: m_resourceManager(resourceManager),
	  m_eventManager(eventManager)
{
	
}

void PhysicsManager::startUp() {
	
}

void PhysicsManager::shutDown() {
	
}

void PhysicsManager::tick(float deltaTime) {
	std::vector <std::shared_ptr<PhysicsHandler>> physicsHandlers = m_resourceManager.findByType<PhysicsHandler>();
	
	std::shared_ptr<PhysicsHandler> a;
	std::shared_ptr<PhysicsHandler> b;

	for (uint32_t i = 0; i < physicsHandlers.size(); i++) {
		for (uint32_t j = i + 1; j < physicsHandlers.size(); j++) {
			 a = physicsHandlers[i];
			 b = physicsHandlers[j];
			if (checkAABBCollision(a, b)) {
				CollisionEvent event;
				event.firstCollider = a;
				event.secondCollider = b;

				m_eventManager.push(event);
			}
		}
	}
}

bool PhysicsManager::checkAABBCollision(const std::shared_ptr<PhysicsHandler>& a, const std::shared_ptr<PhysicsHandler>& b) {
	if (!ResourceManager::isValid(a) || !ResourceManager::isValid(b)) {
		return false;
	}

	glm::vec3 minA = a->getOwner()->getPosition() + a->getBounds().min;
	glm::vec3 maxA = a->getOwner()->getPosition() + a->getBounds().max;

	glm::vec3 minB = b->getOwner()->getPosition() + b->getBounds().min;
	glm::vec3 maxB = b->getOwner()->getPosition() + b->getBounds().max;

	bool ret = (
		minA.x < maxB.x &&
		maxA.x > minB.x &&
		minA.y < maxB.y &&
		maxA.y > minB.y &&
		minA.z < maxB.z &&
		maxA.z > minB.z
	);

	return ret;
}
