#include "Spawnable.h"

bool Spawnable::isPendingDestruction() {
	return m_pendingDestruction;
}

void Spawnable::destroy() {
	m_pendingDestruction = true;
	setCanTick(false);
}

bool Spawnable::canTick() {
	return m_canTick;
}

void Spawnable::setCanTick(bool value) {
	m_canTick = value;
}
