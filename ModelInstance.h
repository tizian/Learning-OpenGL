#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Material.h"
#include "Shader.h"
#include "ModelAsset.h"

// A ModelAsset with transformation, material, texture, ...

class ModelInstance
{
public:
	ModelInstance(glm::vec3 position, glm::fquat orientation, glm::vec3 scale, Material material);
	ModelInstance(glm::vec3 position, glm::fquat orientation, glm::vec3 scale);
	ModelInstance(glm::vec3 position);
	ModelInstance();


	void setPosition(glm::vec3 position);
	void setOrientation(glm::fquat orientation);
	void setScale(glm::vec3 scale);
	void setMaterial(Material material);
	void setModel(ModelAsset modelAsset);

	glm::vec3 getPosition();
	glm::fquat getOrientation();
	glm::vec3 getScale();
	Material getMaterial();
	ModelAsset getModel(); 

	// Returns translation matrix
	glm::mat4 translation();

	// Returns scale matrix
	glm::mat4 scale();

	// Returns rotation matrix
	glm::mat4 rotation();

	// Returns model matrix (model = translation * rotation * scale)
	glm::mat4 model();

	// Renders the Model
	void render(Shader shader);

private:
	ModelAsset *m_model;
	Material m_material;
	glm::vec3 m_position;
	glm::fquat m_orientation;
	glm::vec3 m_scale;
};