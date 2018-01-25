#include <SDL2/SDL.h>

#include "InputHandler.h"
#include "PhysicsHandler.h"
#include "Spawnable/GameObject/GameObject.h"

float InputHandler::getHorizontalMovement() {
	float movement = m_horizontalMovement ? m_horizontalMovement : getDirectionToCenter();
	float position = getOwner()->getPosition().x;

	if (MAX_DISTANCE_FROM_CENTER - glm::abs(position) < POSITION_TOLERANCE) {
		movement = glm::sign(movement) != glm::sign(position) ? movement : 0.0f;
	}

	return movement;
}

float InputHandler::getDirectionToCenter() {
	if (getOwner()->getPosition().x > 0.0f + POSITION_TOLERANCE) {
		return -1.0f;
	} 
	
	if (getOwner()->getPosition().x < 0.0f - POSITION_TOLERANCE) {
		return 1.0f;
	}

	return 0.0f;
}

void InputHandler::tick(float deltaTime) {
	if (!getOwner()) {
		return;
	}

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			m_quit = true;
		} else if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
			switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					m_quit = true;
					break;
				case SDLK_d:
					m_horizontalMovement += 1.0f;
					break;
				case SDLK_a:
					m_horizontalMovement -= 1.0f;
					break;
			}
		} else if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
				case SDLK_d:
					m_horizontalMovement -= 1.0f;
					break;
				case SDLK_a:
					m_horizontalMovement += 1.0f;
					break;
			}
		}
	}

	m_horizontalMovement = glm::clamp(m_horizontalMovement, -1.0f, 1.0f);

	m_forwardMovement = 1.0f;

	glm::vec3 velocity;
	glm::vec3 forwardVector = getOwner()->getForwardVector();
	glm::vec3 rightVector   = getOwner()->getRightVector();

	velocity += forwardVector * m_forwardMovement * m_forwardSpeed;
	velocity += rightVector * getHorizontalMovement() * m_horizontalSpeed;

	std::shared_ptr<PhysicsHandler> physicsHandler = getOwner()->getPhysicsHandler();
	if (physicsHandler) {
		physicsHandler->addForce(velocity);
	}
}

void InputHandler::load() {

}

void InputHandler::unLoad() {

}

bool InputHandler::wantsQuit() const {
	return m_quit;
}
