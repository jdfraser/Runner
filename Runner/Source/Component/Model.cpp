#include "Model.h"

Model::Model(std::vector<GLfloat> vertices, std::vector<GLfloat> UVs, std::weak_ptr<Material> mat) 
	: m_vertices(vertices),
	  m_UVs(UVs),
	  m_material(mat)
{
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	glGenBuffers(1, &m_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(GLuint), m_vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &m_UVBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_UVBufferID);
	glBufferData(GL_ARRAY_BUFFER, m_UVs.size() * sizeof(GLuint), m_UVs.data(), GL_STATIC_DRAW);
}

void Model::tick(float deltaTime) {

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

std::weak_ptr<Material> Model::getMaterial() {
	return m_material;
}

Model::~Model() {
	glDeleteBuffers(1, &m_UVBufferID);
	glDeleteBuffers(1, &m_vertexBufferID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}

