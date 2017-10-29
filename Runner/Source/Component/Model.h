#pragma once

#include <vector>
#include <memory>

#include "Component.h"
#include "Component/Material.h"
#include "Component/Transform.h"

class Model : public Component
{
private:
	std::vector<GLfloat> m_vertices;
	std::vector<GLfloat> m_UVs;

	GLuint m_vertexArrayID;
	GLuint m_vertexBufferID;
	GLuint m_UVBufferID;

	std::shared_ptr<class Material> m_material;

public:
	void setVertices(std::vector<GLfloat> m_vertices);
	
	void setUVs(std::vector<GLfloat> m_UVs);

	void setMaterial(std::shared_ptr<class Material> material);

	GLuint getVertexArray();

	GLuint getVertexBuffer();

	GLuint getUVBuffer();

	std::shared_ptr<Material> getMaterial();

protected:
	virtual bool onInitialize() override;

	virtual bool onDestroy() override;
};