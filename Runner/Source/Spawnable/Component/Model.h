#pragma once

#include "Component.h"
#include "Spawnable/Component/Material.h"
#include "Engine/Bounds.h"

class Model : public Component
{
private:
	GLuint m_vertexArrayID;
	GLuint m_vertexBufferID;
	GLuint m_UVBufferID;

	Bounds m_bounds;

	std::vector<GLfloat> m_vertices;
	std::vector<GLfloat> m_texCoords;

	std::shared_ptr<class Material> m_material;

	bool m_rendering = false;
	std::vector<GLuint> m_attribArraysInUse;
	
public:
	virtual void load() override;

	virtual void unLoad() override;

	void beginRender();

	void endRender();

	void setVertices(std::vector<GLfloat> vertices);
	
	void setTexCoords(std::vector<GLfloat> texCoords);

	void setMaterial(std::shared_ptr<class Material> material);

	glm::mat4 getTransformMatrix();

	Bounds getBounds();

	void writeTextureToShader(GLuint uniformLocation);

	void writeVerticesToShader(GLuint verticesIndex);

	void writeTexCoordsToShader(GLuint texCoordsIndex);

private:
	void calculateBounds();
};