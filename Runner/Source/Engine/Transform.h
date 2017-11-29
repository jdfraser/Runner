#pragma once

#include "Util/Common.h"

class Transform
{
private:
	bool m_matrixDirty;
	
	glm::mat4 m_matrix;

	glm::vec3 m_scale;
	glm::vec3 m_rotation;
	glm::vec3 m_position;

public:
	Transform();

	glm::vec3 getScale() const;

	void setScale(glm::vec3 scale);

	glm::vec3 getRotation() const;

	void setRotation(glm::vec3 rotation);

	glm::vec3 getPosition() const;

	void setPosition(glm::vec3 position);

	glm::mat4 getMatrix();

	glm::vec3 getForwardVector();

	glm::vec3 getRightVector();

	glm::vec3 getUpVector();

};