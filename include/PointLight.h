#pragma once

#include <glm/glm.hpp>

#include "Shader.h"

// A simple point light.

class PointLight
{
public:
	PointLight();
	PointLight(glm::vec3 position);
	PointLight(glm::vec3 position, glm::vec3 color);

	void setPosition(glm::vec3 position);
	void setSpecularColor(glm::vec3 specularColor);
	void setDiffuseColor(glm::vec3 diffuseColor);
	void setAmbientColor(glm::vec3 ambientColor);
	void setAttenuationFactor(float attenuationFactor);

	glm::vec3 getPosition() const;
	glm::vec3 getSpecularColor() const;
	glm::vec3 getDiffuseColor() const;
	glm::vec3 getAmbientColor() const;
	float getAttenuationFactor() const;

	// Sets appropriate uniform values for the given shader program
	void setUniforms(Shader shader);

private:
	glm::vec3 m_position;

	glm::vec3 m_Ls;	// Specular light color
	glm::vec3 m_Ld;	// Diffuse light color
	glm::vec3 m_La; // Ambient light color

	float m_att;	// Attenuation factor
};
