#pragma once

#include "Component.h"

class InputHandler : public Component
{
private:
	float m_forwardSpeed = 3.0f;
	float m_rightSpeed   = 1.5f;
	float m_mouseSpeed   = 0.05f;

	bool m_quit = false;

	float m_forward = 0.0f;
	float m_right   = 0.0f;

public:
	virtual void tick(float deltaTime) override;

	virtual void load() override;

	virtual void unLoad() override;

	bool wantsQuit() const;
};