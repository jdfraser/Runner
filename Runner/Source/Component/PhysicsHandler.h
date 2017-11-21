#pragma once

#include "Component.h"

class PhysicsHandler : public Component
{
private:
	glm::vec3 m_velocity;

public:
	virtual void tick(float deltaTime) override;

	virtual void load() override;

	virtual void unLoad() override;

	void setVelocity(glm::vec3 velocity);

	glm::vec3 getVelocity();

};