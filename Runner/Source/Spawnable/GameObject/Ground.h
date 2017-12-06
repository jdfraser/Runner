#pragma once

#include "GameObject.h"

class Ground : public GameObject
{
private:
	std::shared_ptr<class Model> m_groundModel;

public:
	std::shared_ptr<class Model> getGroundModel();

	void setGroundModel(std::shared_ptr<class Model> model);

};