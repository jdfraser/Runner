#pragma once

#include "Component.h"

class InputHandler : public Component
{
private:
	const float POSITION_TOLERANCE = 0.1f;
	const float MAX_DISTANCE_FROM_CENTER = 1.5f;

	float m_forwardSpeed      = 5.0f;
	float m_horizontalSpeed   = 4.0f;
	float m_jumpForce         = 4.0f;

	bool m_quit = false;

	float m_forwardMovement    = 0.0f;
	float m_horizontalMovement = 0.0f;

	float getHorizontalMovement();

	float getDirectionToCenter();

public:
	virtual void tick(float deltaTime) override;

	virtual void load() override;

	virtual void unLoad() override;

	bool wantsQuit() const;
};