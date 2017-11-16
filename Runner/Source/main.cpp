#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "Common.h"

#include "Manager/ResourceManager.h"
#include "Manager/GraphicsManager.h"
#include "Manager/GameplayManager.h"

#include "GameObject/GameObject.h"
#include "GameObject/GameObjectFactory.h"

#include "Component/InputHandler.h"

int main(int argc, char* argv[]) {

	ResourceManager g_resourceManager;
	GraphicsManager g_graphicsManager(g_resourceManager);
	GameplayManager g_gameplayManager(g_resourceManager, g_graphicsManager);

	g_resourceManager.startUp();
	g_graphicsManager.startUp();
	g_gameplayManager.startUp();

	std::shared_ptr<GameObject> player = g_resourceManager.getPlayer();
	std::shared_ptr<InputHandler> inputHandler = player->getInputHandler();

	while (!inputHandler->wantsQuit()) {
		static float lastTime = static_cast<float>(SDL_GetTicks());
		float currentTime = static_cast<float>(SDL_GetTicks());
		float deltaTime = (currentTime - lastTime) / 1000.0f;

		g_resourceManager.tick(deltaTime);
		g_gameplayManager.tick(deltaTime);
		g_graphicsManager.tick(deltaTime);

		lastTime = currentTime;
	}

	g_gameplayManager.shutDown();
	g_graphicsManager.shutDown();
	g_resourceManager.shutDown();

    return EXIT_SUCCESS;
}