#include "EventManager.h"

void EventManager::startUp() {

}

void EventManager::shutDown() {

}

void EventManager::push(CollisionEvent event) {
	m_collisionEvents.push(event);
}

CollisionEvent EventManager::getNextCollisionEvent() {
	CollisionEvent event = m_collisionEvents.front();
	m_collisionEvents.pop();

	return event;
}

bool EventManager::hasCollisionEvent() {
	return !m_collisionEvents.empty();
}
