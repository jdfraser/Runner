#include "Material.h"

void Material::load() {
	
}

void Material::unLoad() {
	
}

void Material::setTexture(GLuint textureID) {
	m_textureID = textureID;
}

GLuint Material::getTexture() const {
	return m_textureID;
}

void Material::setShader(GLuint shaderID) {
	m_shaderID = shaderID;
}

GLuint Material::getShader() const {
	return m_shaderID;
}

GLuint Material::getShaderVerticesIndex() {
	return 0;
}

GLuint Material::getShaderTexCoordsIndex() {
	return 1;
}
