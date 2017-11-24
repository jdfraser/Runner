#pragma once

#include "Manager.h"

class PhysicsManager : public Manager
{
private:
	class ResourceManager& m_resourceManager;

public:
	PhysicsManager(class ResourceManager& resourceManager);

	virtual void startUp() override;

	virtual void shutDown() override;

	virtual void tick(float deltaTime) override;

	bool checkAABBCollision(const std::shared_ptr<class PhysicsHandler>& a, const std::shared_ptr<class PhysicsHandler>& b);
};