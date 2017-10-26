#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SOIL2/SOIL2.h>

#include <iostream>
#include <vector>

#include "Manager/GraphicsManager.h"
#include "GameObject/GameObject.h"
#include "Component/Model.h"
#include "Graphics/Material.h"

#include "Util/shader.h"

float speed = 3.0f;
float mouseSpeed = 0.05f;

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

const std::vector<GLfloat> vertices = {
	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f
};

const std::vector<GLfloat> texCoords = {
	0.000059f, 1.0f - 0.000004f,
	0.000103f, 1.0f - 0.336048f,
	0.335973f, 1.0f - 0.335903f,
	1.000023f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.336024f, 1.0f - 0.671877f,
	0.667969f, 1.0f - 0.671889f,
	1.000023f, 1.0f - 0.000013f,
	0.668104f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.000059f, 1.0f - 0.000004f,
	0.335973f, 1.0f - 0.335903f,
	0.336098f, 1.0f - 0.000071f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.336024f, 1.0f - 0.671877f,
	1.000004f, 1.0f - 0.671847f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.668104f, 1.0f - 0.000013f,
	0.335973f, 1.0f - 0.335903f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.668104f, 1.0f - 0.000013f,
	0.336098f, 1.0f - 0.000071f,
	0.000103f, 1.0f - 0.336048f,
	0.000004f, 1.0f - 0.671870f,
	0.336024f, 1.0f - 0.671877f,
	0.000103f, 1.0f - 0.336048f,
	0.336024f, 1.0f - 0.671877f,
	0.335973f, 1.0f - 0.335903f,
	0.667969f, 1.0f - 0.671889f,
	1.000004f, 1.0f - 0.671847f,
	0.667979f, 1.0f - 0.335851f
};

int main(int argc, char* argv[]) {
	GraphicsManager graphicsManager;
	graphicsManager.startUp();

	// TODO: move this into a manager
	GLuint programID = LoadShaders("Assets/Shaders/default.vert", "Assets/Shaders/default.frag");
	GLuint textureID = SOIL_load_OGL_texture("Assets/Textures/uvtemplate.DDS", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_DDS_LOAD_DIRECT);

	Material material(programID);
	material.setTexture(textureID);

	Model model(vertices, texCoords, &material);

	GameObject box;
	box.setModel(&model);

	graphicsManager.addObject(&box);

	GameObject player;
	player.getTransform().setPosition(glm::vec3(0.0f, 0.0f, 10.0f));

	graphicsManager.setCamera(&(player.getTransform()));

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

		glm::vec3 position      = player.getTransform().getPosition();
		glm::vec3 forwardVector = player.getTransform().getForwardVector();
		glm::vec3 rightVector   = player.getTransform().getRightVector();
		glm::vec3 upVector      = player.getTransform().getUpVector();

		float horizontalRotation = static_cast<float>(xPos - (WINDOW_WIDTH / 2)) * deltaTime * mouseSpeed;
		float verticalRotation   = static_cast<float>(yPos - (WINDOW_HEIGHT / 2)) * deltaTime * mouseSpeed;

		player.getTransform().addRotation(glm::vec3(verticalRotation, horizontalRotation, 0.f));

		position += forwardVector * (forward - backward) * deltaTime * speed;
		position += rightVector * (right - left) * deltaTime * speed;

		player.getTransform().setPosition(position);

		graphicsManager.draw();

		lastTime = currentTime;
	}

    return EXIT_SUCCESS;
}