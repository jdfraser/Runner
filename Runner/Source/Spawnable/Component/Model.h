#pragma once

#include "Component.h"
#include "Spawnable/Component/Material.h"
#include "Engine/Transform.h"
#include "Engine/Bounds.h"

class Model : public Component
{
private:
	GLuint m_vertexArrayID;
	GLuint m_vertexBufferID;
	GLuint m_UVBufferID;

	Transform m_transform;
	glm::mat4 m_worldTransformMatrix;
	Bounds m_bounds;

	std::vector<GLfloat> m_vertices;
	std::vector<GLfloat> m_texCoords;

	std::shared_ptr<class Material> m_material;

	bool m_rendering = false;
	std::vector<GLuint> m_attribArraysInUse;

	void calculateBounds();

public:
	virtual void load() override;

	virtual void unLoad() override;

	virtual void tick(float deltaTime) override;

	void beginRender();

	void endRender();

	void setVertices(std::vector<GLfloat> vertices);
	
	void setTexCoords(std::vector<GLfloat> texCoords);

	void setMaterial(std::shared_ptr<class Material> material);

	Transform& getTransform();

	glm::mat4 getLocalTransformMatrix() const;

	glm::mat4 getWorldTransformMatrix() const;

	Bounds getBounds() const;

	void writeTextureToShader(GLuint uniformLocation);

	void writeVerticesToShader(GLuint verticesIndex);

	void writeTexCoordsToShader(GLuint texCoordsIndex);
};