#pragma once

#include <vector>
#include <memory>

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

	std::weak_ptr<Material> m_material;

public:
	Model() {}

	Model(std::vector<GLfloat> vertices, std::vector<GLfloat> UVs, std::weak_ptr<Material> mat);

	virtual void tick(float deltaTime);

	GLuint getVertexArray();

	GLuint getVertexBuffer();

	GLuint getUVBuffer();

	std::weak_ptr<Material> getMaterial();

	~Model();
};