#include "Material.h"

Material::Material(GLuint programID) : m_programID(programID) {

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

