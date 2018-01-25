#include "glm/gtx/normalize_dot.hpp"

#include "PhysicsHandler.h"
#include "Spawnable/GameObject/GameObject.h"

void PhysicsHandler::resetForce() {
	m_force = glm::vec3(0.0f, 0.0f, 0.0f);
}

void PhysicsHandler::applyGravity(float deltaTime) {
	if (!isFalling()) {
		return;
	}

	m_velocity += glm::vec3(0.0f, m_gravity, 0.0f) * deltaTime;
}

bool PhysicsHandler::isFalling() {
	if (!m_hasPhysics) {
		return false;
	}

	return m_falling;
}

void PhysicsHandler::stopFalling() {
	if (!m_hasPhysics) {
		return;
	}

	m_velocity.y = 0.0f;
	m_falling    = false;
}

void PhysicsHandler::snapToTop(std::shared_ptr<PhysicsHandler> other) {
	if (!m_hasPhysics) {
		return;
	}
	
	float newY         = other->getWorldBounds().max.y + (getLocalBounds().getHeight() / 2);
	glm::vec3 position = getOwner()->getPosition();

	getOwner()->setPosition(glm::vec3(position.x, newY, position.z));
}

void PhysicsHandler::tick(float deltaTime) {
	assert(getOwner() != nullptr);

	applyGravity(deltaTime);

	getOwner()->setPosition(getOwner()->getPosition() + (m_velocity + m_force) * deltaTime);

	m_worldBounds = m_bounds.applyTransformation(getOwner()->getTransformMatrix());

	resetForce();
}

void PhysicsHandler::load() {
	
}

void PhysicsHandler::unLoad() {
	
}

void PhysicsHandler::addForce(glm::vec3 force) {
	m_force += force;
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

void PhysicsHandler::setHasPhysics(bool hasPhysics) {
	m_hasPhysics = hasPhysics;
}

void PhysicsHandler::setFalling(bool falling) {
	m_falling = falling;
}

void PhysicsHandler::collidedWith(std::shared_ptr<PhysicsHandler> other) {
	if (getOwner()->getPosition().y > other->getWorldBounds().max.y) {
		stopFalling();
		snapToTop(other);
	}
}
