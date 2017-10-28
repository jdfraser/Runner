#include "Component.h"

std::weak_ptr<class GameObject> Component::getOwner() {
	return m_owner;
}

void Component::setOwner(std::weak_ptr<class GameObject> owner) {
	m_owner = owner;
}

