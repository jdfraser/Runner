#pragma once
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include <vector>

#include "Manager.h"

class GraphicsManager : public Manager
{
private:
	SDL_Window* m_window;
	SDL_GLContext m_context;

	class Transform* m_camera;

	std::vector<class GameObject*> m_gameObjects;

public:
	virtual void startUp() override;

	virtual void shutDown() override;

	void setCamera(class Transform* camera);

	void addObject(class GameObject* gameObject);

	void draw();

	void present();

private:

	int getWindowWidth();

	int getWindowHeight();

	glm::uvec2 getWindowCenter();

	float getAspectRatio();
};