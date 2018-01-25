#include "glm/gtx/normalize_dot.hpp"

#include "PhysicsHandler.h"
#include "Spawnable/GameObject/GameObject.h"

void PhysicsHandler::resetVelocity() {
	m_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
}

void PhysicsHandler::applyGravity() {
	if (!isFalling()) {
		return;
	}

	addVelocity(glm::vec3(0.0f, m_gravity, 0.0f));
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

	m_falling = false;
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

	getOwner()->setPosition(getOwner()->getPosition() + m_velocity * deltaTime);

	m_worldBounds = m_bounds.applyTransformation(getOwner()->getTransformMatrix());

	resetVelocity();
	applyGravity();
}

void PhysicsHandler::load() {
	
}

void PhysicsHandler::unLoad() {
	
}

void PhysicsHandler::addVelocity(glm::vec3 velocity) {
	m_velocity += velocity;
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
