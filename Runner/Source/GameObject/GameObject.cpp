#include "GameObject.h"

Transform& GameObject::getTransform() {
	return m_transform;
}

std::weak_ptr<Model> GameObject::getModel() {
	return m_model;
}

void GameObject::setModel(std::weak_ptr<Model> model) {
	m_model = model;
}

