#pragma once

#include "Component.h"
#include "Engine/Bounds.h"

class PhysicsHandler : public Component
{
private:
	glm::vec3 m_velocity;

	Bounds m_bounds;
	Bounds m_worldBounds;

public:
	virtual void tick(float deltaTime) override;

	virtual void load() override;

	virtual void unLoad() override;

	void setVelocity(glm::vec3 velocity);

	glm::vec3 getVelocity() const;

	Bounds getLocalBounds() const;

	Bounds getWorldBounds() const;

	void setLocalBounds(Bounds bounds);

};