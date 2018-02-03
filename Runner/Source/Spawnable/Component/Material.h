#pragma once

#include <GL/glew.h>

#include "Component.h"

class Material : public Component
{
private:
	GLuint m_textureID;
	GLuint m_shaderID;

public:
	virtual void load() override;

	virtual void unLoad() override;

	void setTexture(GLuint textureID);

	GLuint getTexture() const;

	void setShader(GLuint shaderID);

	GLuint getShader() const;

	GLuint getShaderVerticesIndex();

	GLuint getShaderTexCoordsIndex();
};