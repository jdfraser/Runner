#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "GraphicsManager.h"
#include "ResourceManager.h"
#include "Util/shader.h"
#include "GameObject/GameObject.h"
#include "Component/Model.h"
#include "Component/Material.h"
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

	m_defaultShader = m_resourceManager.loadShader("default");

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

void GraphicsManager::setCamera(std::shared_ptr<GameObject> camera) {
	m_camera = camera;
}

std::shared_ptr<class GameObject> GraphicsManager::getCamera() {
	if (!m_camera) {
		m_camera = m_resourceManager.getPlayer();
	}

	return m_camera;
}

void GraphicsManager::tick(float deltaTime) {
	draw();
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

	glm::vec3 pos = getCamera()->getTransform().getPosition();

	glm::mat4 viewMatrix = glm::lookAt(
		pos,
		pos + getCamera()->getTransform().getForwardVector(),
		getCamera()->getTransform().getUpVector()
	);

	for (std::shared_ptr<Model> model : m_resourceManager.findByType<Model>()) {
		if (!ResourceManager::isValid(model)) {
			continue;
		}

		glm::mat4 modelMatrix = model->getTransformMatrix();

		glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

		glUseProgram(m_defaultShader);

		// Write the MVP matrix
		glUniformMatrix4fv(
			glGetUniformLocation(m_defaultShader, "MVP"),
			1,
			GL_FALSE,
			&mvp[0][0]
		);
		
		model->beginRender();
			model->writeTextureToShader(glGetUniformLocation(m_defaultShader, "textureSampler"));
			model->writeVerticesToShader(0);
			model->writeTexCoordsToShader(1);
			glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
		model->endRender();
	}

	SDL_GL_SwapWindow(m_window);
}

int GraphicsManager::getWindowWidth() {
	return m_windowWidth;
}

int GraphicsManager::getWindowHeight() {
	return m_windowHeight;
}

glm::uvec2 GraphicsManager::getWindowCenter() {
	glm::uvec2 center;
	center.x = getWindowWidth() / 2;
	center.y = getWindowHeight() / 2;

	return center;
}

float GraphicsManager::getAspectRatio() {
	return static_cast<float>(getWindowWidth()) / static_cast<float>(getWindowHeight());
}

float GraphicsManager::getMaxViewDistance() {
	return 10.0f;
}

