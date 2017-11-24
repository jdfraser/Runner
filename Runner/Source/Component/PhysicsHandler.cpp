#include "PhysicsHandler.h"
#include "GameObject/GameObject.h"

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

glm::vec3 PhysicsHandler::getVelocity() {
	return m_velocity;
}

Bounds PhysicsHandler::getBounds() {
	return m_bounds;
}

void PhysicsHandler::setBounds(Bounds bounds) {
	m_bounds = bounds;
}
