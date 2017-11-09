#pragma once
#include <SDL2/SDL.h>

#include "Manager.h"

class GraphicsManager final : public Manager
{
private:
	class ResourceManager& m_resourceManager;

	SDL_Window* m_window;
	SDL_GLContext m_context;

	GLuint m_defaultShader;

	std::shared_ptr<class GameObject> m_camera;

public:
	GraphicsManager(class ResourceManager& resourceManager);

	~GraphicsManager() = default;

	virtual void startUp() override;

	virtual void shutDown() override;

	void setCamera(std::shared_ptr<class GameObject> gameObject);

	std::shared_ptr<class GameObject> getCamera();

	void draw();

private:

	int getWindowWidth();

	int getWindowHeight();

	glm::uvec2 getWindowCenter();

	float getAspectRatio();
};