#pragma once

#include "Manager.h"

class PhysicsManager : public Manager
{
private:
	class ResourceManager& m_resourceManager;

	class EventManager& m_eventManager;

public:
	PhysicsManager(class ResourceManager& resourceManager, class EventManager& eventManager);

	virtual void startUp() override;

	virtual void shutDown() override;

	virtual void tick(float deltaTime) override;

	bool checkAABBCollision(const std::shared_ptr<class PhysicsHandler>& a, const std::shared_ptr<class PhysicsHandler>& b);
};