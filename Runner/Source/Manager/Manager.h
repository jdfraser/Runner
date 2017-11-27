#pragma once

#include "Util/Common.h"

class Manager
{
public:
	virtual void startUp()=0;

	virtual void shutDown()=0;

	virtual void tick(float deltaTime) {}
};