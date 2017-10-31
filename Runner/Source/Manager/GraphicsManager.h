#pragma once
#include <SDL2/SDL.h>

#include "Manager.h"

class GraphicsManager final : public Manager
{
private:
	SDL_Window* m_window;
	SDL_GLContext m_context;

	std::shared_ptr<class GameObject> m_camera;

	std::vector<std::shared_ptr<class GameObject>> m_gameObjects;

public:
	virtual void startUp() override;

	virtual void shutDown() override;

	void setCamera(std::shared_ptr<class GameObject> gameObject);

	void addObject(std::shared_ptr<class GameObject> gameObject);

	void draw();

private:

	int getWindowWidth();

	int getWindowHeight();

	glm::uvec2 getWindowCenter();

	float getAspectRatio();
};