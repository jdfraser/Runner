#include "Material.h"

void Material::load() {
	if (m_programID == 0 || m_textureID == 0) {
		Debug::log("Failed to load material");
	}
}

void Material::unLoad() {
	
}

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
