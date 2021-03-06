#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "GraphicsManager.h"
#include "ResourceManager.h"
#include "Util/shader.h"
#include "Spawnable/GameObject/GameObject.h"
#include "Spawnable/Component/Model.h"
#include "Spawnable/Component/Material.h"
#include "Engine/Transform.h"

GraphicsManager::GraphicsManager(ResourceManager& resourceManager)
	: m_resourceManager(resourceManager) {

}

void GraphicsManager::startUp() {
	SDL_VideoInit(nullptr);

	SDL_DisplayMode displayMode;
	if (SDL_GetDesktopDisplayMode(0, &displayMode) != 0) {
		Debug::log(SDL_GetError());

		return;
	}

	m_windowWidth = displayMode.w;
	m_windowHeight = displayMode.h;

	m_window = SDL_CreateWindow(
		"Runner",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		m_windowWidth,
		m_windowHeight,
		SDL_WINDOW_OPENGL
	);

	if (m_window == nullptr) {
		Debug::log("Unable to create window:");
		Debug::log(SDL_GetError());

		return;
	}

	m_context = SDL_GL_CreateContext(m_window);

	if (m_context == nullptr) {
		Debug::log("Unable to create context:");
		Debug::log(SDL_GetError());

		return;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glewInit();

	glClearColor(CLEAR_COLOR.r, CLEAR_COLOR.g, CLEAR_COLOR.b, CLEAR_COLOR.a);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);

	SDL_ShowCursor(SDL_DISABLE);

	glm::uvec2 center = getWindowCenter();
	SDL_WarpMouseInWindow(m_window, center.x, center.y);
}

void GraphicsManager::shutDown() {
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);

	SDL_Quit();
}

void GraphicsManager::tick(float deltaTime) {
	draw();
}

void GraphicsManager::setCamera(std::shared_ptr<GameObject> camera) {
	m_camera = camera;
}

std::shared_ptr<class GameObject> GraphicsManager::getCamera() {
	return m_camera;
}

float GraphicsManager::getMaxViewDistance() const {
	return 10.0f;
}

void GraphicsManager::draw() {
	glm::uvec2 center = getWindowCenter();
	SDL_WarpMouseInWindow(m_window, center.x, center.y);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 projectionMatrix = glm::perspective(
		glm::radians(45.0f),
		getAspectRatio(),
		0.1f,
		100.0f
	);

	glm::vec3 pos = getCamera()->getPosition();

	glm::mat4 viewMatrix = glm::lookAt(
		pos,
		pos + getCamera()->getForwardVector(),
		getCamera()->getUpVector()
	);

	for (std::shared_ptr<Model> model : m_resourceManager.findByType<Model>()) {
		if (!ResourceManager::isValid(model)) {
			continue;
		}

		glm::mat4 mvp = projectionMatrix * viewMatrix * model->getWorldTransformMatrix();
		
		model->beginRender();
			model->writeMVPToShader(mvp);
			model->writeTextureToShader();
			model->writeVerticesToShader();
			model->writeTexCoordsToShader();
			model->draw();
		model->endRender();
	}

	SDL_GL_SwapWindow(m_window);
}

int GraphicsManager::getWindowWidth() const {
	return m_windowWidth;
}

int GraphicsManager::getWindowHeight() const {
	return m_windowHeight;
}

glm::uvec2 GraphicsManager::getWindowCenter() const {
	glm::uvec2 center;
	center.x = getWindowWidth() / 2;
	center.y = getWindowHeight() / 2;

	return center;
}

float GraphicsManager::getAspectRatio() const {
	return static_cast<float>(getWindowWidth()) / static_cast<float>(getWindowHeight());
}

