#include "ModelInstance.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ModelInstance::ModelInstance(const glm::vec3 & position, const glm::fquat & orientation, const glm::vec3 & scale) {
	m_position = position;
	m_orientation = orientation;
	m_scale = scale;
//	m_material = NULL;
	m_model = NULL;
}

ModelInstance::ModelInstance(const glm::vec3 & position) {
	m_position = position;
	m_orientation = glm::fquat(1, 0, 0, 0);
	m_scale = glm::vec3(1, 1, 1);
//	m_material = NULL;
	m_model = NULL;
}

ModelInstance::ModelInstance() {
	m_position = glm::vec3(1, 1, 1);
	m_orientation = glm::fquat(1, 0, 0, 0);
	m_scale = glm::vec3(1, 1, 1);
//	m_material = NULL;
	m_model = NULL;
}

void ModelInstance::setPosition(const glm::vec3 & position) {
	m_position = position;
}

void ModelInstance::setOrientation(const glm::fquat & orientation) {
	m_orientation = orientation;
}

void ModelInstance::setScale(const glm::vec3 & scale) {
	m_scale = scale;
}

void ModelInstance::setMaterial(Material material) {
	m_material = material;
}

void ModelInstance::setModel(ModelAsset * modelAsset) {
    m_model = modelAsset;
}

glm::vec3 ModelInstance::getPosition() const {
	return m_position;
}

glm::fquat ModelInstance::getOrientation() const {
	return m_orientation;
}

glm::vec3 ModelInstance::getScale() const {
	return m_scale;
}

Material ModelInstance::getMaterial() const {
	return m_material;
}

ModelAsset ModelInstance::getModel() const {
    return *m_model;
}

glm::mat4 ModelInstance::translation() const {
	return glm::translate(glm::mat4(), m_position);
}

glm::mat4 ModelInstance::scale() const {
	return glm::scale(glm::mat4(), m_scale);
}

glm::mat4 ModelInstance::rotation() const {
	return glm::toMat4(m_orientation);
}

glm::mat4 ModelInstance::model() const {
	return translation() * rotation() * scale();
}

void ModelInstance::render(Shader * shader, ModelAsset * modelAsset) {
//	shader.use();

    shader->setUniform("model", model());
	
	m_material.setUniforms(shader);

	if (m_model == NULL) {
		printf("ERROR: Can't render ModelInstance. ModelAsset not set.\n");
		exit(-1);
	}
	modelAsset->render();
}