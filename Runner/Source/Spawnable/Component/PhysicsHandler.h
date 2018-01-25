#pragma once

#include "Component.h"
#include "Engine/Bounds.h"

class PhysicsHandler : public Component
{
private:
	float m_gravity   = -9.8f;
	bool m_hasPhysics = false;
	bool m_falling    = true;

	glm::vec3 m_force;
	glm::vec3 m_velocity;

	Bounds m_bounds;
	Bounds m_worldBounds;

	void resetForce();

	void applyGravity(float deltaTime);

	bool isFalling();

	void stopFalling();

	void snapToTop(std::shared_ptr<PhysicsHandler> other);

public:
	virtual void tick(float deltaTime) override;

	virtual void load() override;

	virtual void unLoad() override;

	void addForce(glm::vec3 velocity);

	glm::vec3 getVelocity() const;

	Bounds getLocalBounds() const;

	Bounds getWorldBounds() const;

	void setLocalBounds(Bounds bounds);

	void setHasPhysics(bool hasGravity);

	void setFalling(bool falling);

	void collidedWith(std::shared_ptr<PhysicsHandler> other);
};