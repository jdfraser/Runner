#include <SDL2/SDL.h>

#include "InputHandler.h"
#include "PhysicsHandler.h"
#include "GameObject/GameObject.h"

void InputHandler::tick(float deltaTime) {
	if (!getOwner()) {
		return;
	}

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			m_quit = true;
		} else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					m_quit = true;
					break;
				case SDLK_d:
					m_right = 1.0f;
					break;
				case SDLK_a:
					m_left = 1.0f;
					break;
			}
		} else if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
				case SDLK_d:
					m_right = 0.0f;
					break;
				case SDLK_a:
					m_left = 0.0f;
					break;
			}
		}
	}

	m_forward = 1.0f;

	glm::vec3 velocity;
	glm::vec3 forwardVector = getOwner()->getTransform().getForwardVector();
	glm::vec3 rightVector = getOwner()->getTransform().getRightVector();
	glm::vec3 upVector = getOwner()->getTransform().getUpVector();

	velocity += forwardVector * (m_forward - m_backward) * m_forwardSpeed;
	velocity += rightVector * (m_right - m_left) * m_rightSpeed;

	std::shared_ptr<PhysicsHandler> physicsHandler = getOwner()->getPhysicsHandler();
	if (physicsHandler) {
		physicsHandler->setVelocity(velocity);
	}
}

void InputHandler::load() {

}

void InputHandler::unLoad() {

}

bool InputHandler::wantsQuit() {
	return m_quit;
}
