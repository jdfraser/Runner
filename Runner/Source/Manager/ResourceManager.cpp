#include <SOIL2/SOIL2.h>
#include <tinyobjloader/tiny_obj_loader.h>

#include <algorithm>

#include "ResourceManager.h"

#include "Util/shader.h"

#include "GameObject/GameObject.h"
#include "Component/Model.h"
#include "Component/Material.h"

void ResourceManager::startUp() {
	
}

void ResourceManager::shutDown() {
	for (std::shared_ptr<Component> component : m_components) {
		component->unLoad();
	}
}

void ResourceManager::cleanupDestroyedSpawnables() {
	for (std::shared_ptr<GameObject>& gameObject : m_gameObjects) {
		if (!gameObject->isPendingDestruction()) {
			continue;
		}

		if (!gameObject.unique()) {
			continue;
		}

		gameObject.reset();
	}

	m_gameObjects.erase(
		std::remove_if(
			m_gameObjects.begin(),
			m_gameObjects.end(),
			[](std::shared_ptr<GameObject>& gameObject) { return gameObject == nullptr; }
		),
		m_gameObjects.end()
	);

	for (std::shared_ptr<Component> component : m_components) {
		if (!component->isPendingDestruction()) {
			continue;
		}

		if (!component.unique()) {
			continue;
		}

		component.reset();
	}

	m_components.erase(
		std::remove_if(
			m_components.begin(),
			m_components.end(),
			[](std::shared_ptr<Component>& component) { return component == nullptr; }
		),
		m_components.end()
	);
}

void ResourceManager::loadModelData(const std::shared_ptr<class Model> model, std::string modelName) {
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string errorMessage;

	tinyobj::LoadObj(&attrib, &shapes, &materials, &errorMessage, (MODEL_DIR + modelName + ".obj").c_str(), MODEL_DIR.c_str());

	if (!errorMessage.empty()) {
		Debug::log(errorMessage);
	}

	std::vector<GLfloat> vertices;
	std::vector<GLfloat> texCoords;

	for (tinyobj::shape_t shape : shapes) {
		for (tinyobj::index_t index : shape.mesh.indices) {
			vertices.push_back(attrib.vertices[3 * index.vertex_index]);
			vertices.push_back(attrib.vertices[3 * index.vertex_index + 1]);
			vertices.push_back(attrib.vertices[3 * index.vertex_index + 2]);

			if (index.texcoord_index >= 0) {
				texCoords.push_back(attrib.texcoords[2 * index.texcoord_index]);
				texCoords.push_back(attrib.texcoords[2 * index.texcoord_index + 1]);
			}
		}
	}
	
	std::shared_ptr<Material> material = std::dynamic_pointer_cast<Material>(makeNewComponent<Material>());

	material->setTexture(
		SOIL_load_OGL_texture(
			(TEXTURE_DIR + modelName + ".DDS").c_str(),
			SOIL_LOAD_RGB,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_DDS_LOAD_DIRECT
		)
	);

	material->load();

	model->setMaterial(material);
	model->setVertices(vertices);
	model->setTexCoords(texCoords);
	model->load();
}

std::shared_ptr<class GameObject> ResourceManager::makeNewObject() {
	std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();

	m_gameObjects.push_back(gameObject);

	return gameObject;
}

GLuint ResourceManager::loadShader(std::string shaderName) {
	std::string baseDir = "Assets/Shaders/";

	return LoadShaders((baseDir + shaderName + ".vert").c_str(), (baseDir + shaderName + ".frag").c_str());
}

const std::vector<std::shared_ptr<class GameObject>>& ResourceManager::getDrawObjects() {
	return m_gameObjects;
}

const std::vector<std::shared_ptr<class GameObject>>& ResourceManager::getAllGameObjects() {
	return m_gameObjects;
}

std::shared_ptr<class GameObject> ResourceManager::makeNewPlayer() {
	m_player = std::dynamic_pointer_cast<GameObject>(makeNewObject());
	
	return m_player;
}

const std::shared_ptr<class GameObject> ResourceManager::getPlayer() {
	return m_player;
}

bool ResourceManager::isValid(std::shared_ptr<class Spawnable> spawnableObject) {
	return spawnableObject != nullptr && !spawnableObject->isPendingDestruction();
}

void ResourceManager::tick(float deltaTime) {
	cleanupDestroyedSpawnables();
}
