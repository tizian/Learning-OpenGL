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

PointLight::PointLight(const glm::vec3 & position) {
    m_position = glm::vec3(position);
    m_Ls = glm::vec3(1, 1, 1);
    m_Ld = glm::vec3(1, 1, 1);
    m_La = glm::vec3(1, 1, 1);
    m_att = 0;
}

PointLight::PointLight(const glm::vec3 & position, const glm::vec3 & color) {
    m_position = glm::vec3(position);
    m_Ls = glm::vec3(color);
    m_Ld = glm::vec3(color);
    m_La = glm::vec3(color);
    m_att = 0;
}

void PointLight::setPosition(const glm::vec3 & position) {
	m_position = position;
}

void PointLight::setSpecularColor(const glm::vec3 & specularColor) {
	m_Ls = specularColor;
}

void PointLight::setDiffuseColor(const glm::vec3 & diffuseColor) {
	m_Ld = diffuseColor;
}

void PointLight::setAmbientColor(const glm::vec3 & ambientColor) {
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

void PointLight::setUniforms(Shader * shader) {
	shader->use();
    shader->setUniform("light.position", m_position);
    shader->setUniform("light.Ls", m_Ls);
    shader->setUniform("light.Ld", m_Ld);
    shader->setUniform("light.La", m_La);
    shader->setUniform("light.attenuation", m_att);
}