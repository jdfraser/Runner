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

	std::shared_ptr<class GameObject> m_camera;

	void draw();

	int getWindowWidth() const;

	int getWindowHeight() const;

	glm::uvec2 getWindowCenter() const;

	float getAspectRatio() const;

public:
	GraphicsManager(class ResourceManager& resourceManager);

	~GraphicsManager() = default;

	virtual void startUp() override;

	virtual void shutDown() override;

	virtual void tick(float deltaTime) override;

	void setCamera(std::shared_ptr<class GameObject> gameObject);

	std::shared_ptr<class GameObject> getCamera();

	float getMaxViewDistance() const;

};