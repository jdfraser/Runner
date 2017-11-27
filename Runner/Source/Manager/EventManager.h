#pragma once

#include <queue>

#include "Manager.h"
#include "Event/CollisionEvent.h"

class EventManager : public Manager
{
private:
	std::queue<CollisionEvent> m_collisionEvents;

public:
	virtual void startUp() override;

	virtual void shutDown() override;

	void push(CollisionEvent event);

	CollisionEvent getNextCollisionEvent();

	bool hasCollisionEvent();
};