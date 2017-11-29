#pragma once

#include "Util/Common.h"
#include "Spawnable/Spawnable.h"

class Component : public Spawnable
{
private:
	std::shared_ptr<class GameObject> m_owner;

public:
	std::shared_ptr<class GameObject> getOwner();

	void setOwner(std::shared_ptr<class GameObject> owner);

	virtual void tick(float deltaTime);

	virtual void load()=0;

	virtual void unLoad()=0;

	virtual void destroy() final override;

};