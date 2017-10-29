#pragma once

#include <GL/glew.h>

#include "Component.h"

class Material : public Component
{
private:
	GLuint m_programID;
	GLuint m_textureID;

public:

	void setProgramID(GLuint programID);

	GLuint getProgramID();

	void setTexture(GLuint textureID);

	GLuint getTexture();

protected:
	virtual bool onInitialize() override;

	virtual bool onDestroy() override;
};