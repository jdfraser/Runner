#include "PhysicsHandler.h"
#include "Spawnable/GameObject/GameObject.h"

void PhysicsHandler::tick(float deltaTime) {
	assert(getOwner() != nullptr);

	getOwner()->setPosition(getOwner()->getPosition() + m_velocity * deltaTime);

	m_worldBounds = m_bounds.applyTransformation(getOwner()->getTransformMatrix());
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

Bounds PhysicsHandler::getLocalBounds() const {
	return m_bounds;
}

Bounds PhysicsHandler::getWorldBounds() const {
	return m_worldBounds;
}

void PhysicsHandler::setLocalBounds(Bounds bounds) {
	m_bounds = bounds;
}
