#pragma once

#include <glm/glm.hpp>

#include "Component.h"

class Transform : public Component
{
private:
	
	glm::vec3 m_scale;
	glm::vec3 m_rotation;
	glm::vec3 m_position;

public:

	Transform();

	virtual void tick(float deltaTime);

	glm::vec3 getScale();

	glm::vec3 getRotation();

	void addRotation(glm::vec3 rotation);

	glm::vec3 getPosition();

	void setPosition(glm::vec3 position);

	glm::mat4 toMatrix();

	glm::vec3 getForwardVector();

	glm::vec3 getRightVector();

	glm::vec3 getUpVector();

};