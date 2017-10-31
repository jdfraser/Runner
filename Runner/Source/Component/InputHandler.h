#pragma once

#include "Component.h"

class InputHandler : public Component
{
private:
	float m_speed = 3.0f;
	float m_mouseSpeed = 0.05f;

	bool m_quit = false;

	float m_forward  = 0.0f;
	float m_backward = 0.0f;
	float m_left     = 0.0f;
	float m_right    = 0.0f;

public:
	virtual void tick(float deltaTime) override;

	virtual void load() override;

	virtual void unLoad() override;

	bool wantsQuit();
};