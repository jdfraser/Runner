#include "Model.h"
#include "Spawnable/GameObject/GameObject.h"

void Model::calculateBounds() {
	glm::vec3 min(0.0f, 0.0f, 0.0f);
	glm::vec3 max(0.0f, 0.0f, 0.0f);

	assert(m_vertices.size() % 3 == 0);

	for (uint32_t i = 0; i < m_vertices.size(); i += 3) {
		float x = m_vertices[i];
		float y = m_vertices[i + 1];
		float z = m_vertices[i + 2];

		min.x = glm::min(x, min.x);
		min.y = glm::min(y, min.y);
		min.z = glm::min(z, min.z);

		max.x = glm::max(x, max.x);
		max.y = glm::max(y, max.y);
		max.z = glm::max(z, max.z);
	}

	m_bounds.min = min;
	m_bounds.max = max;
}

void Model::load() {
	if (!m_material || m_vertices.size() == 0 || (m_material->getTexture() && m_texCoords.size() == 0)) {
		Debug::log("Failed to load model\n");

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

	calculateBounds();
}

void Model::unLoad() {
	glDeleteBuffers(1, &m_UVBufferID);
	glDeleteBuffers(1, &m_vertexBufferID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}

void Model::tick(float deltaTime) {
	m_transform.rebuildMatrix();

	if (getOwner() != nullptr) {
		m_worldTransformMatrix = getOwner()->getTransformMatrix() * getLocalTransformMatrix();
	}
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

std::shared_ptr<Material> Model::getMaterial() {
	return m_material;
}

Transform& Model::getTransform() {
	return m_transform;
}

glm::mat4 Model::getLocalTransformMatrix() const {
	return m_transform.getMatrix();
}

glm::mat4 Model::getWorldTransformMatrix() const {
	return m_worldTransformMatrix;
}

Bounds Model::getBounds() const {
	return m_bounds;
}

void Model::beginRender() {
	assert(!m_rendering);

	m_rendering = true;

	glUseProgram(getMaterial()->getShader());
}

void Model::draw() {
	assert(m_rendering);

	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
}

void Model::endRender() {
	assert(m_rendering);

	m_rendering = false;

	for (GLuint index : m_attribArraysInUse) {
		glDisableVertexAttribArray(index);
	}

	m_attribArraysInUse.clear();
}

void Model::writeMVPToShader(glm::mat4 mvp) {
	glUniformMatrix4fv(
		glGetUniformLocation(getMaterial()->getShader(), "MVP"),
		1,
		GL_FALSE,
		&mvp[0][0]
	);
}

void Model::writeTextureToShader() {
	assert(m_rendering);

	if (!m_material->getTexture()) {
		return;
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_material->getTexture());
	glUniform1i(glGetUniformLocation(getMaterial()->getShader(), "textureSampler"), 0);
}

void Model::writeVerticesToShader() {
	assert(m_rendering);

	GLuint verticesIndex = getMaterial()->getShaderVerticesIndex();

	m_attribArraysInUse.push_back(verticesIndex);

	glEnableVertexAttribArray(verticesIndex);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glVertexAttribPointer(verticesIndex, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Model::writeTexCoordsToShader() {
	assert(m_rendering);

	if (!m_material->getTexture()) {
		return;
	}

	GLuint texCoordsIndex = getMaterial()->getShaderTexCoordsIndex();

	m_attribArraysInUse.push_back(texCoordsIndex);

	glEnableVertexAttribArray(texCoordsIndex);
	glBindBuffer(GL_ARRAY_BUFFER, m_UVBufferID);
	glVertexAttribPointer(texCoordsIndex, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}
