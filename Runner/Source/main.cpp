#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <iostream>
#include <vector>
#include <memory>

#include "Manager/GraphicsManager.h"
#include "Manager/ResourceManager.h"

#include "GameObject/GameObject.h"
#include "GameObject/GameObjectFactory.h"

#include "Component/InputHandler.h"

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

int main(int argc, char* argv[]) {

	GraphicsManager g_graphicsManager;
	ResourceManager g_resourceManager;

	g_graphicsManager.startUp();
	g_resourceManager.startUp();

	GameObjectFactory factory(g_resourceManager);

	g_graphicsManager.addObject(factory.makeCube());

	std::weak_ptr<GameObject> player = factory.makePlayer();
	g_graphicsManager.setCamera(player);

	std::shared_ptr<GameObject> spPlayer = player.lock();
	std::shared_ptr<InputHandler> spInputHandler = spPlayer->getInputHandler().lock();

	spPlayer->getTransform().setPosition(glm::vec3(0.0f, 0.0f, 10.0f));

	while (!spInputHandler->wantsQuit()) {
		static float lastTime = static_cast<float>(SDL_GetTicks());
		float currentTime = static_cast<float>(SDL_GetTicks());
		float deltaTime = (currentTime - lastTime) / 1000.0f;

		spPlayer->tick(deltaTime);

		g_graphicsManager.draw();

		lastTime = currentTime;
	}

    return EXIT_SUCCESS;
}