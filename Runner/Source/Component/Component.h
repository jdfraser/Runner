#pragma once

#include <memory>

class Component
{
private:
	bool valid = false;

	std::shared_ptr<class GameObject> m_owner;

protected:
	std::shared_ptr<class GameObject> getOwner();

	virtual bool onInitialize();

	virtual bool onDestroy();

public:
	void setOwner(std::shared_ptr<class GameObject> owner);

	virtual void tick(float deltaTime);

	void initialize();

	bool isValid();

	void destroy();

};