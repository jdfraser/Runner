#include "Component.h"

std::shared_ptr<class GameObject> Component::getOwner() {
	return m_owner;
}

void Component::setOwner(std::shared_ptr<class GameObject> owner) {
	m_owner = owner;
}

void Component::tick(float deltaTime) {
	if (!canTick()) {
		return;
	}
}

void Component::destroy() {
	Spawnable::destroy();

	m_owner.reset();
}
