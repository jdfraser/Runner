#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <iostream>
#include <vector>
#include <memory>

#include "Manager/GraphicsManager.h"
#include "Manager/ResourceManager.h"

#include "GameObject/GameObject.h"
#include "GameObject/GameObjectFactory.h"

float speed = 3.0f;
float mouseSpeed = 0.05f;

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

int main(int argc, char* argv[]) {

	GraphicsManager g_graphicsManager;
	ResourceManager g_resourceManager;

	g_graphicsManager.startUp();
	g_resourceManager.startUp();

	GameObjectFactory factory(g_resourceManager);

	g_graphicsManager.addObject(factory.makeCube());

	std::weak_ptr<GameObject> wpPlayer = g_resourceManager.getNewObject();
	g_graphicsManager.setCamera(wpPlayer);

	std::shared_ptr<GameObject> player = wpPlayer.lock();

	player->getTransform().setPosition(glm::vec3(0.0f, 0.0f, 10.0f));

	float forward = 0.0f;
	float backward = 0.0f;
	float left = 0.0f;
	float right = 0.0f;

	bool quit = false;
	while (!quit) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			} else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						quit = true;
						break;
					case SDLK_w:
						forward = 1.0f;
						break;
					case SDLK_s:
						backward = 1.0f;
						break;
					case SDLK_d:
						right = 1.0f;
						break;
					case SDLK_a:
						left = 1.0f;
						break;
				}
			} else if (event.type == SDL_KEYUP) {
				switch (event.key.keysym.sym) {
					case SDLK_w:
						forward = 0.0f;
						break;
					case SDLK_s:
						backward = 0.0f;
						break;
					case SDLK_d:
						right = 0.0f;
						break;
					case SDLK_a:
						left = 0.0f;
						break;
				}
			}
		}

		static float lastTime = static_cast<float>(SDL_GetTicks());
		float currentTime = static_cast<float>(SDL_GetTicks());
		float deltaTime = (currentTime - lastTime) / 1000.0f;

		int xPos;
		int yPos;

		SDL_GetMouseState(&xPos, &yPos);

		glm::vec3 position      = player->getTransform().getPosition();
		glm::vec3 forwardVector = player->getTransform().getForwardVector();
		glm::vec3 rightVector   = player->getTransform().getRightVector();
		glm::vec3 upVector      = player->getTransform().getUpVector();

		float horizontalRotation = static_cast<float>(xPos - (WINDOW_WIDTH / 2)) * deltaTime * mouseSpeed;
		float verticalRotation   = static_cast<float>(yPos - (WINDOW_HEIGHT / 2)) * deltaTime * mouseSpeed;

		player->getTransform().addRotation(glm::vec3(verticalRotation, horizontalRotation, 0.f));

		position += forwardVector * (forward - backward) * deltaTime * speed;
		position += rightVector * (right - left) * deltaTime * speed;

		player->getTransform().setPosition(position);

		g_graphicsManager.draw();

		lastTime = currentTime;
	}

    return EXIT_SUCCESS;
}