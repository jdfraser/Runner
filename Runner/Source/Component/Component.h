#pragma once

#include "Common.h"

class Component
{
private:
	std::shared_ptr<class GameObject> m_owner;

protected:
	std::shared_ptr<class GameObject> getOwner();

public:
	void setOwner(std::shared_ptr<class GameObject> owner);

	virtual void tick(float deltaTime);

	virtual void load()=0;

	virtual void unLoad()=0;

};