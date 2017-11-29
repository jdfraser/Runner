#pragma once

class Spawnable
{
private:
	bool m_pendingDestruction;

	bool m_canTick = true;

public:
	virtual void tick(float deltaTime)=0;

	bool canTick();

	void setCanTick(bool value);

	bool isPendingDestruction();

	virtual void destroy();
};