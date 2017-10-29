#include "Material.h"

void Material::setProgramID(GLuint programID) {
	m_programID = programID;
}

GLuint Material::getProgramID() {
	return m_programID;
}

void Material::setTexture(GLuint textureID) {
	m_textureID = textureID;
}

GLuint Material::getTexture() {
	return m_textureID;
}

bool Material::onInitialize() {
	return (m_programID > 0 && m_textureID > 0);
}

bool Material::onDestroy() {
	return true;
}
