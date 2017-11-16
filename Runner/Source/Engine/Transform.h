#pragma once

#include "Common.h"

class Transform
{
private:
	
	glm::vec3 m_scale;
	glm::vec3 m_rotation;
	glm::vec3 m_position;

public:

	Transform();

	glm::vec3 getScale();

	void setScale(glm::vec3 scale);

	glm::vec3 getRotation();

	void setRotation(glm::vec3 rotation);

	glm::vec3 getPosition();

	void setPosition(glm::vec3 position);

	glm::mat4 toMatrix();

	glm::vec3 getForwardVector();

	glm::vec3 getRightVector();

	glm::vec3 getUpVector();

};