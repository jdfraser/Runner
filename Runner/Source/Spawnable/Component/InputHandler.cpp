#include <SDL2/SDL.h>

#include "InputHandler.h"
#include "PhysicsHandler.h"
#include "Spawnable/GameObject/GameObject.h"

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
					m_right += 1.0f;
					break;
				case SDLK_a:
					m_right -= 1.0f;
					break;
			}
		} else if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
				case SDLK_d:
					m_right -= 1.0f;
					break;
				case SDLK_a:
					m_right += 1.0f;
					break;
			}
		}
	}

	m_right   = glm::clamp(m_right, -1.0f, 1.0f);
	m_forward = 1.0f;

	glm::vec3 velocity;
	glm::vec3 forwardVector = getOwner()->getForwardVector();
	glm::vec3 rightVector   = getOwner()->getRightVector();

	velocity += forwardVector * m_forward * m_forwardSpeed;
	velocity += rightVector * m_right * m_rightSpeed;

	std::shared_ptr<PhysicsHandler> physicsHandler = getOwner()->getPhysicsHandler();
	if (physicsHandler) {
		physicsHandler->setVelocity(velocity);
	}
}

void InputHandler::load() {

}

void InputHandler::unLoad() {

}

bool InputHandler::wantsQuit() const {
	return m_quit;
}
