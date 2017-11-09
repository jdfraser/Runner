#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "Common.h"

#include "Manager/GraphicsManager.h"
#include "Manager/ResourceManager.h"

#include "GameObject/GameObject.h"
#include "GameObject/GameObjectFactory.h"

#include "Component/InputHandler.h"

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

int main(int argc, char* argv[]) {

	ResourceManager g_resourceManager;
	GraphicsManager g_graphicsManager(g_resourceManager);

	g_resourceManager.startUp();
	g_graphicsManager.startUp();

	GameObjectFactory factory(g_resourceManager);

	factory.makeGround();

	std::shared_ptr<GameObject> player = factory.makePlayer();
	g_graphicsManager.setCamera(player);

	std::shared_ptr<InputHandler> inputHandler = player->getInputHandler();

	player->getTransform().setPosition(glm::vec3(0.0f, 0.0f, 10.0f));

	while (!inputHandler->wantsQuit()) {
		static float lastTime = static_cast<float>(SDL_GetTicks());
		float currentTime = static_cast<float>(SDL_GetTicks());
		float deltaTime = (currentTime - lastTime) / 1000.0f;

		player->tick(deltaTime);

		g_graphicsManager.draw();

		lastTime = currentTime;
	}

    return EXIT_SUCCESS;
}