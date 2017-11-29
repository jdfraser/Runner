#include "PhysicsHandler.h"
#include "Spawnable/GameObject/GameObject.h"

void PhysicsHandler::tick(float deltaTime) {
	getOwner()->setPosition(getOwner()->getPosition() + m_velocity * deltaTime);
}

void PhysicsHandler::load() {
	
}

void PhysicsHandler::unLoad() {
	
}

void PhysicsHandler::setVelocity(glm::vec3 velocity) {
	m_velocity = velocity;
}

glm::vec3 PhysicsHandler::getVelocity() const {
	return m_velocity;
}

Bounds PhysicsHandler::getBounds() const {
	return m_bounds;
}

void PhysicsHandler::setBounds(Bounds bounds) {
	m_bounds = bounds;
}
