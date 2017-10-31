#pragma once

#include <GL/glew.h>

#include "Component.h"

class Material : public Component
{
private:
	GLuint m_programID;
	GLuint m_textureID;

public:
	virtual void load() override;

	virtual void unLoad() override;

	void setProgramID(GLuint programID);

	GLuint getProgramID();

	void setTexture(GLuint textureID);

	GLuint getTexture();
};