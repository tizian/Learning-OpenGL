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
	ModelInstance(const glm::vec3 & position, const glm::fquat & orientation, const glm::vec3 & scale);
	ModelInstance(const glm::vec3 & position);
	ModelInstance();

	void setPosition(const glm::vec3 & position);
	void setOrientation(const glm::fquat & orientation);
	void setScale(const glm::vec3 & scale);
	void setMaterial(Material material);
	void setModel(ModelAsset * modelAsset);

	glm::vec3 getPosition() const;
	glm::fquat getOrientation() const;
	glm::vec3 getScale() const;
	Material getMaterial() const;
	ModelAsset getModel() const;

	// Returns translation matrix
	glm::mat4 translation() const;

	// Returns scale matrix
	glm::mat4 scale() const;

	// Returns rotation matrix
	glm::mat4 rotation() const;

	// Returns model matrix (model = translation * rotation * scale)
	glm::mat4 model() const;

	// Renders the Model
	void render(Shader * shader, ModelAsset * modelAsset);

private:
	ModelAsset * m_model;
    
	Material m_material;
    
	glm::vec3 m_position;
	glm::fquat m_orientation;
	glm::vec3 m_scale;
};