#pragma once

#include "Component.h"
#include "Component/Material.h"
#include "Component/Transform.h"

class Model : public Component
{
private:
	bool m_rendering = false;
	std::vector<GLuint> m_attribArraysInUse;

	std::vector<GLfloat> m_vertices;
	std::vector<GLfloat> m_texCoords;

	GLuint m_vertexArrayID;
	GLuint m_vertexBufferID;
	GLuint m_UVBufferID;

	std::shared_ptr<class Material> m_material;

public:
	virtual void load() override;

	virtual void unLoad() override;

	void beginRender();

	void endRender();

	void setVertices(std::vector<GLfloat> vertices);
	
	void setTexCoords(std::vector<GLfloat> texCoords);

	void setMaterial(std::shared_ptr<class Material> material);

	void writeTextureToShader(GLuint uniformLocation);

	void writeVerticesToShader(GLuint verticesIndex);

	void writeTexCoordsToShader(GLuint texCoordsIndex);
};