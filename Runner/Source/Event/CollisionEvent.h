#pragma once

#include "Event.h"

struct CollisionEvent : public Event
{
	std::shared_ptr<class PhysicsHandler> firstCollider;

	std::shared_ptr<class PhysicsHandler> secondCollider;
};