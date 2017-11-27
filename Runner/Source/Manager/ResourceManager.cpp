#include <SOIL2/SOIL2.h>
#include <tinyobjloader/tiny_obj_loader.h>

#include <algorithm>

#include "ResourceManager.h"

#include "Util/shader.h"

#include "Spawnable/GameObject/GameObject.h"
#include "Spawnable/Component/Model.h"
#include "Spawnable/Component/Material.h"

void ResourceManager::startUp() {
	
}

void ResourceManager::shutDown() {
	for (std::shared_ptr<Component> component : findByType<Component>()) {
		component->unLoad();
	}
}

void ResourceManager::removeDestroyed() {
	for (std::shared_ptr<Spawnable>& object : m_spawnedObjects) {
		if (!object->isPendingDestruction()) {
			continue;
		}

		if (!object.unique()) {
			continue;
		}

		object.reset();
	}

	eraseNullPointers<std::shared_ptr<Spawnable>>(m_spawnedObjects);
}

void ResourceManager::loadModelData(const std::shared_ptr<Model> model, std::string modelName) {
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
	
	std::shared_ptr<Material> material = cast<Material>(make<Material>());

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

GLuint ResourceManager::loadShader(std::string shaderName) {
	std::string baseDir = "Assets/Shaders/";

	return LoadShaders((baseDir + shaderName + ".vert").c_str(), (baseDir + shaderName + ".frag").c_str());
}

std::shared_ptr<GameObject> ResourceManager::makeNewPlayer() {
	m_player = cast<GameObject>(make<GameObject>());
	
	return m_player;
}

const std::shared_ptr<GameObject> ResourceManager::getPlayer() {
	return m_player;
}

bool ResourceManager::isValid(std::shared_ptr<Spawnable> spawnableObject) {
	return spawnableObject != nullptr && !spawnableObject->isPendingDestruction();
}

void ResourceManager::tick(float deltaTime) {
	removeDestroyed();
}