#include "PointLight.h"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

PointLight::PointLight() {
    m_position = glm::vec3(0, 0, 0);
    m_Ls = glm::vec3(1, 1, 1);
    m_Ld = glm::vec3(1, 1, 1);
    m_La = glm::vec3(1, 1, 1);
    m_att = 0;
}

PointLight::PointLight(glm::vec3 position) {
    m_position = glm::vec3(position);
    m_Ls = glm::vec3(1, 1, 1);
    m_Ld = glm::vec3(1, 1, 1);
    m_La = glm::vec3(1, 1, 1);
    m_att = 0;
}

PointLight::PointLight(glm::vec3 position, glm::vec3 color) {
    m_position = glm::vec3(position);
    m_Ls = glm::vec3(color);
    m_Ld = glm::vec3(color);
    m_La = glm::vec3(color);
    m_att = 0;
}

void PointLight::setPosition(glm::vec3 position) {
	m_position = position;
}

void PointLight::setSpecularColor(glm::vec3 specularColor) {
	m_Ls = specularColor;
}

void PointLight::setDiffuseColor(glm::vec3 diffuseColor) {
	m_Ld = diffuseColor;
}

void PointLight::setAmbientColor(glm::vec3 ambientColor) {
	m_La = ambientColor;
}

void PointLight::setAttenuationFactor(float attenuationFactor) {
	m_att = attenuationFactor;
}

glm::vec3 PointLight::getPosition() const {
	return m_position;
}

glm::vec3 PointLight::getSpecularColor() const {
	return m_Ls;
}

glm::vec3 PointLight::getDiffuseColor() const {
	return m_Ld;
}

glm::vec3 PointLight::getAmbientColor() const {
	return m_La;
}

float PointLight::getAttenuationFactor() const {
	return m_att;
}

void PointLight::setUniforms(Shader shader) {
	shader.use();
	GLint posLoc = shader.getUniformLocation("light.position");
	GLint LsLoc = shader.getUniformLocation("light.Ls");
	GLint LdLoc = shader.getUniformLocation("light.Ld");
	GLint LaLoc = shader.getUniformLocation("light.La");
	GLint attLoc = shader.getUniformLocation("light.attenuation");

	glUniform3fv(posLoc, 1, glm::value_ptr(m_position));
	glUniform3fv(LsLoc, 1, glm::value_ptr(m_Ls));
	glUniform3fv(LdLoc, 1, glm::value_ptr(m_Ld));
	glUniform3fv(LaLoc, 1, glm::value_ptr(m_La));
	glUniform1fv(attLoc, 1, &m_att);
}