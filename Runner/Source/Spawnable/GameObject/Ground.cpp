#include "Ground.h"

std::shared_ptr<class Model> Ground::getGroundModel() {
	return m_groundModel;
}

void Ground::setGroundModel(std::shared_ptr<class Model> model) {
	m_groundModel = model;
}