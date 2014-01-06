#pragma once

#include <glm/glm.hpp>

#include "Shader.h"

// Material properties to be used in a shader

class Material
{
public:
	Material(glm::vec3 specularFactor, glm::vec3 diffuseFactor, glm::vec3 ambientFactor, float specularExp);
	Material();

	void setSpecularFactor(glm::vec3 specularFactor);
	void setDiffuseFactor(glm::vec3 diffuseFactor);
	void setAmbientFactor(glm::vec3 ambientFactor);
	void setShininess(float shininess);

	glm::vec3 getSpecularFactor();
	glm::vec3 getDiffuseFactor();
	glm::vec3 getAmbientFactor();
	float getShininess();

	// Sets appropriate uniform values for the given shader program
	void setUniforms(Shader shader);

private:
	glm::vec3 m_Ks;	// Specular reflectant factor
	glm::vec3 m_Kd;	// Diffuse reflectant factor
	glm::vec3 m_Ka; // Ambient reflectant factor
	float m_shininess;	// Specular exponent
};