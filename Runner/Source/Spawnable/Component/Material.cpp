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