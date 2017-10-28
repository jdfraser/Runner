#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "InputHandler.h"
#include "GameObject/GameObject.h"

void InputHandler::tick(float deltaTime) {
	std::shared_ptr<GameObject> spOwner = getOwner().lock();

	if (!spOwner) {
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
				case SDLK_w:
					m_forward = 1.0f;
					break;
				case SDLK_s:
					m_backward = 1.0f;
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
				case SDLK_w:
					m_forward = 0.0f;
					break;
				case SDLK_s:
					m_backward = 0.0f;
					break;
				case SDLK_d:
					m_right = 0.0f;
					break;
				case SDLK_a:
					m_left = 0.0f;
					break;
			}
		}
	}

	int xPos;
	int yPos;

	SDL_GetMouseState(&xPos, &yPos);

	glm::vec3 position = spOwner->getTransform().getPosition();
	glm::vec3 forwardVector = spOwner->getTransform().getForwardVector();
	glm::vec3 rightVector = spOwner->getTransform().getRightVector();
	glm::vec3 upVector = spOwner->getTransform().getUpVector();

	// TODO: get window dimensions from GraphicsManager
	float horizontalRotation = static_cast<float>(xPos - (1024 / 2)) * deltaTime * m_mouseSpeed;
	float verticalRotation = static_cast<float>(yPos - (768 / 2)) * deltaTime * m_mouseSpeed;

	spOwner->getTransform().addRotation(glm::vec3(verticalRotation, horizontalRotation, 0.f));

	position += forwardVector * (m_forward - m_backward) * deltaTime * m_speed;
	position += rightVector * (m_right - m_left) * deltaTime * m_speed;

	spOwner->getTransform().setPosition(position);
}

bool InputHandler::wantsQuit() {
	return m_quit;
}
