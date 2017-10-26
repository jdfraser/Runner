#include "GameObject.h"

Transform& GameObject::getTransform() {
	return m_transform;
}

Model* GameObject::getModel() {
	return m_model;
}

void GameObject::setModel(Model* model) {
	m_model = model;
}

