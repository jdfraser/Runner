#include "Component.h"

std::shared_ptr<class GameObject> Component::getOwner() {
	return m_owner;
}

bool Component::onInitialize() {
	return true;
}

bool Component::onDestroy() {
	return true;
}

void Component::setOwner(std::shared_ptr<class GameObject> owner) {
	m_owner = owner;
}

void Component::tick(float deltaTime) {

}

void Component::initialize() {
	valid = onInitialize();
}

bool Component::isValid() {
	return valid;
}

void Component::destroy() {
	if (!isValid()) {
		return;
	}

	valid = !onDestroy();
}

