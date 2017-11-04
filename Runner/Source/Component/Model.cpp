#include "Model.h"

void Model::load() {
	if (!m_material || m_vertices.size() == 0 || (m_material->getTexture() && m_texCoords.size() == 0)) {
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
	glBufferData(GL_ARRAY_BUFFER, m_texCoords.size() * sizeof(GLuint), m_texCoords.data(), GL_STATIC_DRAW);
}

void Model::unLoad() {
	glDeleteBuffers(1, &m_UVBufferID);
	glDeleteBuffers(1, &m_vertexBufferID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}

void Model::beginRender() {
	assert(!m_rendering);

	m_rendering = true;
}

void Model::endRender() {
	assert(m_rendering);

	m_rendering = false;

	for (GLuint index : m_attribArraysInUse) {
		glDisableVertexAttribArray(index);
	}

	m_attribArraysInUse.clear();
}

void Model::setVertices(std::vector<GLfloat> vertices) {
	m_vertices = vertices;
}

void Model::setTexCoords(std::vector<GLfloat> texCoords) {
	m_texCoords = texCoords;
}

void Model::setMaterial(std::shared_ptr<class Material> material) {
	m_material = material;
}

void Model::writeTextureToShader(GLuint uniformLocation) {
	assert(m_rendering);

	if (!m_material->getTexture()) {
		return;
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_material->getTexture());
	glUniform1i(uniformLocation, 0);
}

void Model::writeVerticesToShader(GLuint verticesIndex) {
	assert(m_rendering);

	m_attribArraysInUse.push_back(verticesIndex);

	glEnableVertexAttribArray(verticesIndex);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glVertexAttribPointer(verticesIndex, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Model::writeTexCoordsToShader(GLuint texCoordsIndex) {
	assert(m_rendering);

	if (!m_material->getTexture()) {
		return;
	}

	m_attribArraysInUse.push_back(texCoordsIndex);

	glEnableVertexAttribArray(texCoordsIndex);
	glBindBuffer(GL_ARRAY_BUFFER, m_UVBufferID);
	glVertexAttribPointer(texCoordsIndex, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}