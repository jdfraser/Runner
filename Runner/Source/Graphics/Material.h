#pragma once

#include <GL/glew.h>

class Material
{
private:
	GLuint m_programID;
	GLuint m_textureID;

public:

	Material(GLuint programID);

	GLuint getProgramID();

	void setTexture(GLuint textureID);

	GLuint getTexture();
};