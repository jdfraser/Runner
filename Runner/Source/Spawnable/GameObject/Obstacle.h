#pragma once

#include "GameObject.h"

class Obstacle : public GameObject
{
private:
	std::shared_ptr<class Model> m_obstacleModel;

public:
	std::shared_ptr<class Model> getObstacleModel();

	void setObstacleModel(std::shared_ptr<class Model> model);
};