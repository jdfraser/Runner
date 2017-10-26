#pragma once

#include <vector>

#include "Component.h"
#include "Graphics/Material.h"
#include "Component/Transform.h"

class Model : public Component
{
private:
	std::vector<GLfloat> m_vertices;
	std::vector<GLfloat> m_UVs;

	GLuint m_vertexArrayID;
	GLuint m_vertexBufferID;
	GLuint m_UVBufferID;

	Material* m_material;

public:
	Model() {}

	Model(std::vector<GLfloat> vertices, std::vector<GLfloat> UVs, Material* material);

	GLuint getVertexArray();

	GLuint getVertexBuffer();

	GLuint getUVBuffer();

	Material* getMaterial();

	~Model();
};