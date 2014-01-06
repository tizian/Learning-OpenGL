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

glm::vec3 Material::getSpecularFactor() {
	return m_Ks;
}

glm::vec3 Material::getDiffuseFactor() {
	return m_Kd;
}

glm::vec3 Material::getAmbientFactor() {
	return m_Ka;
}

float Material::getShininess() {
	return m_shininess;
}

void Material::setUniforms(Shader shader) {
	shader.use();
	GLint KsLoc = shader.getUniformLocation("material.Ks");
	GLint KdLoc = shader.getUniformLocation("material.Kd");
	GLint KaLoc = shader.getUniformLocation("material.Ka");
	GLint shininessLoc = shader.getUniformLocation("material.shininess");

	glUniform3fv(KsLoc, 1, glm::value_ptr(m_Ks));
	glUniform3fv(KdLoc, 1, glm::value_ptr(m_Kd));
	glUniform3fv(KaLoc, 1, glm::value_ptr(m_Ka));
	glUniform1fv(shininessLoc, 1, &m_shininess);
}