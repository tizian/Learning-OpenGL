#include "Material.h"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

Material::Material(glm::vec3 specularFactor, glm::vec3 diffuseFactor, glm::vec3 ambientFactor, float shininess) {
	m_Ks = glm::vec3(specularFactor);
	m_Kd = glm::vec3(diffuseFactor);
	m_Ka = glm::vec3(ambientFactor);
	m_shininess = shininess;
}

Material::Material() {
	m_Ks = glm::vec3(1, 1, 1);
	m_Kd = glm::vec3(1, 1, 1);
	m_Ka = glm::vec3(1, 1, 1);
	m_shininess = 1;
}

void Material::setSpecularFactor(glm::vec3 specularFactor) {
	m_Ks = specularFactor;
}

void Material::setDiffuseFactor(glm::vec3 diffuseFactor) {
	m_Kd = diffuseFactor;
}

void Material::setAmbientFactor(glm::vec3 ambientFactor) {
	m_Ka = ambientFactor;
}

void Material::setShininess(float shininess) {
	m_shininess = shininess;
}

glm::vec3 Material::getSpecularFactor() const {
	return m_Ks;
}

glm::vec3 Material::getDiffuseFactor() const {
	return m_Kd;
}

glm::vec3 Material::getAmbientFactor() const {
	return m_Ka;
}

float Material::getShininess() const {
	return m_shininess;
}

void Material::setUniforms(Shader shader) {
	shader.use();
    shader.setUniform("material.Ks", m_Ks);
    shader.setUniform("material.Kd", m_Kd);
    shader.setUniform("material.Ka", m_Ka);
    shader.setUniform("material.shininess", m_shininess);
}