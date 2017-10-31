#pragma once

#include "Common.h"

class Manager
{
public:
	virtual void startUp()=0;

	virtual void shutDown()=0;
};
