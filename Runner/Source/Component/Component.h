#pragma once

#include <memory>

class Component
{
private:
	std::weak_ptr<class GameObject> m_owner;

protected:
	std::weak_ptr<class GameObject> getOwner();

public:
	void setOwner(std::weak_ptr<class GameObject> owner);

	virtual void tick(float deltaTime)=0;
};