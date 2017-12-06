#include "Obstacle.h"

std::shared_ptr<class Model> Obstacle::getObstacleModel() {
	return m_obstacleModel;
}

void Obstacle::setObstacleModel(std::shared_ptr<class Model> model) {
	m_obstacleModel = model;
}

