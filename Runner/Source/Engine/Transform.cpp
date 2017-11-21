#include "Transform.h"

#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

Transform::Transform() : m_scale(1.0f, 1.0f, 1.0f) {

}

glm::vec3 Transform::getScale() {
	return m_scale;
}

void Transform::setScale(glm::vec3 scale) {
	m_matrixDirty = true;

	m_scale = scale;
}

glm::vec3 Transform::getRotation() {
	return m_rotation;
}

void Transform::setRotation(glm::vec3 rotation) {
	m_matrixDirty = true;

	m_rotation = rotation;
}

glm::vec3 Transform::getPosition() {
	return m_position;
}

void Transform::setPosition(glm::vec3 position) {
	m_matrixDirty = true;

	m_position = position;
}

glm::mat4 Transform::getMatrix() {
	if (m_matrixDirty) {
		m_matrixDirty = false;
		m_matrix      = glm::translate(m_position) *
						glm::eulerAngleXYZ(m_rotation.x, m_rotation.y, m_rotation.z) * 
						glm::scale(m_scale);
	}

	return m_matrix;
}

glm::vec3 Transform::getForwardVector() {
	glm::vec4 forward(0.0f, 0.0f, -1.0f, 0.0f);
	forward = forward * getMatrix();

	return glm::vec3(forward.x, forward.y, forward.z);
}

glm::vec3 Transform::getRightVector() {
	glm::vec4 right(1.0f, 0.0f, 0.0f, 0.0f);
	right = right * getMatrix();

	return glm::vec3(right.x, right.y, right.z);
}

glm::vec3 Transform::getUpVector() {
	glm::vec4 up(0.0f, 1.0f, 0.0f, 0.0f);
	up = up * getMatrix();

	return glm::vec3(up.x, up.y, up.z);
}

