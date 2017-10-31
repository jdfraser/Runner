#include "Model.h"

void Model::load() {
	if (!m_material || m_vertices.size() == 0 || m_UVs.size() == 0) {
		Debug::log("Failed to load model");

		return;
	}

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	glGenBuffers(1, &m_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(GLuint), m_vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &m_UVBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_UVBufferID);
	glBufferData(GL_ARRAY_BUFFER, m_UVs.size() * sizeof(GLuint), m_UVs.data(), GL_STATIC_DRAW);
}

void Model::unLoad() {
	glDeleteBuffers(1, &m_UVBufferID);
	glDeleteBuffers(1, &m_vertexBufferID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}

void Model::setVertices(std::vector<GLfloat> vertices) {
	m_vertices = vertices;
}

void Model::setUVs(std::vector<GLfloat> UVs) {
	m_UVs = UVs;
}

void Model::setMaterial(std::shared_ptr<class Material> material) {
	m_material = material;
}

GLuint Model::getVertexArray() {
	return m_vertexArrayID;
}

GLuint Model::getVertexBuffer() {
	return m_vertexBufferID;
}

GLuint Model::getUVBuffer() {
	return m_UVBufferID;
}

std::shared_ptr<Material> Model::getMaterial() {
	return m_material;
}

