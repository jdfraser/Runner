#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "Util/Common.h"

#include "Manager/ResourceManager.h"
#include "Manager/GraphicsManager.h"
#include "Manager/GameplayManager.h"
#include "Manager/PhysicsManager.h"
#include "Manager/EventManager.h"

#include "Spawnable/GameObject/GameObject.h"
#include "Spawnable/GameObject/GameObjectFactory.h"

#include "Spawnable/Component/InputHandler.h"

int main(int argc, char* argv[]) {

	ResourceManager g_resourceManager;
	EventManager g_eventManager;
	GraphicsManager g_graphicsManager(g_resourceManager);
	PhysicsManager g_physicsManager(g_resourceManager, g_eventManager);
	GameplayManager g_gameplayManager(g_resourceManager, g_graphicsManager, g_eventManager);

	g_resourceManager.startUp();
	g_graphicsManager.startUp();
	g_physicsManager.startUp();
	g_gameplayManager.startUp();
	g_eventManager.startUp();

	std::shared_ptr<GameObject> player = g_resourceManager.getPlayer();
	std::shared_ptr<InputHandler> inputHandler = player->getInputHandler();

	while (!inputHandler->wantsQuit()) {
		static float lastTime = static_cast<float>(SDL_GetTicks());
		float currentTime = static_cast<float>(SDL_GetTicks());
		float deltaTime = (currentTime - lastTime) / 1000.0f;

		g_resourceManager.tick(deltaTime);
		g_physicsManager.tick(deltaTime);
		g_gameplayManager.tick(deltaTime);
		g_graphicsManager.tick(deltaTime);

		lastTime = currentTime;
	}

	g_eventManager.shutDown();
	g_gameplayManager.shutDown();
	g_physicsManager.shutDown();
	g_graphicsManager.shutDown();
	g_resourceManager.shutDown();

    return EXIT_SUCCESS;
}