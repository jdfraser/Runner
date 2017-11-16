#include <SDL2/SDL.h>

#include "InputHandler.h"
#include "GameObject/GameObject.h"

void InputHandler::tick(float deltaTime) {
	std::shared_ptr<GameObject> owner = getOwner();

	if (!owner) {
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

	glm::vec3 position = owner->getTransform().getPosition();
	glm::vec3 forwardVector = owner->getTransform().getForwardVector();
	glm::vec3 rightVector = owner->getTransform().getRightVector();
	glm::vec3 upVector = owner->getTransform().getUpVector();

	position += forwardVector * (m_forward - m_backward) * deltaTime * m_forwardSpeed;
	position += rightVector * (m_right - m_left) * deltaTime * m_rightSpeed;

	owner->getTransform().setPosition(position);
}

void InputHandler::load() {

}

void InputHandler::unLoad() {

}

bool InputHandler::wantsQuit() {
	return m_quit;
}
