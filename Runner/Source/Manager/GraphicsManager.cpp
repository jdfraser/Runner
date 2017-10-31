#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "GraphicsManager.h"
#include "Util/shader.h"
#include "GameObject/GameObject.h"
#include "Component/Transform.h"
#include "Component/Model.h"
#include "Component/Material.h"

void GraphicsManager::startUp() {
	m_window = SDL_CreateWindow(
		"Hello World",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		getWindowWidth(),
		getWindowHeight(),
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

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

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

void GraphicsManager::addObject(std::shared_ptr<GameObject> gameObject) {
	m_gameObjects.push_back(gameObject);
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

	glm::vec3 pos = m_camera->getTransform().getPosition();

	glm::mat4 viewMatrix = glm::lookAt(
		pos,
		pos + m_camera->getTransform().getForwardVector(),
		m_camera->getTransform().getUpVector()
	);

	for (std::shared_ptr<GameObject> gameObject : m_gameObjects) {
		std::shared_ptr<Model> model       = gameObject->getModel();

		if (!model) {
			continue;
		}

		std::shared_ptr<Material> material = model->getMaterial();

		if (!material) {
			continue;
		}

		glUseProgram(material->getProgramID());

		glm::mat4 modelMatrix = gameObject->getTransform().toMatrix();

		glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

		// Write the MVP matrix
		glUniformMatrix4fv(
			glGetUniformLocation(material->getProgramID(), "MVP"),
			1,
			GL_FALSE,
			&mvp[0][0]
		);

		// Write the texture data
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, material->getTexture());
		glUniform1i(glGetUniformLocation(material->getProgramID(), "textureSampler"), 0);

		// Write the vertex data
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, model->getVertexBuffer());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		// Write the texture coordinates
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, model->getUVBuffer());
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		// Draw
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
		glDisableVertexAttribArray(0);
	}

	SDL_GL_SwapWindow(m_window);
}

int GraphicsManager::getWindowWidth() {
	return 1024;
}

int GraphicsManager::getWindowHeight() {
	return 768;
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

