#pragma once
#include <SDL2/SDL.h>

#include "Manager.h"

class GraphicsManager final : public Manager
{
private:
	const glm::vec4 CLEAR_COLOR = {0.5f, 0.5f, 0.5f, 1.0f};

	class ResourceManager& m_resourceManager;

	SDL_Window* m_window;
	SDL_GLContext m_context;

	int m_windowWidth;
	int m_windowHeight;

	GLuint m_defaultShader;

	std::shared_ptr<class GameObject> m_camera;

public:
	GraphicsManager(class ResourceManager& resourceManager);

	~GraphicsManager() = default;

	virtual void startUp() override;

	virtual void shutDown() override;

	virtual void tick(float deltaTime) override;

	void setCamera(std::shared_ptr<class GameObject> gameObject);

	std::shared_ptr<class GameObject> getCamera();

	float getMaxViewDistance();

private:

	void draw();

	int getWindowWidth();

	int getWindowHeight();

	glm::uvec2 getWindowCenter();

	float getAspectRatio();
};