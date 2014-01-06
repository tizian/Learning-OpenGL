#include "ModelInstance.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ModelInstance::ModelInstance(glm::vec3 position, glm::fquat orientation, glm::vec3 scale, Material material) {
	m_position = position;
	m_orientation = orientation;
	m_scale = scale;
	m_material = material;
	m_model = NULL;
}

ModelInstance::ModelInstance(glm::vec3 position, glm::fquat orientation, glm::vec3 scale) {
	m_position = position;
	m_orientation = orientation;
	m_scale = scale;
	m_material = Material();
	m_model = NULL;
}

ModelInstance::ModelInstance(glm::vec3 position) {
	m_position = position;
	m_orientation = glm::fquat(1, 0, 0, 0);
	m_scale = glm::vec3(1, 1, 1);
	m_material = Material();
	m_model = NULL;
}

ModelInstance::ModelInstance() {
	m_position = glm::vec3(1, 1, 1);
	m_orientation = glm::fquat(1, 0, 0, 0);
	m_scale = glm::vec3(1, 1, 1);
	m_material = Material();
	m_model = NULL;
}

void ModelInstance::setPosition(glm::vec3 position) {
	m_position = position;
}

void ModelInstance::setOrientation(glm::fquat orientation) {
	m_orientation = orientation;
}

void ModelInstance::setScale(glm::vec3 scale) {
	m_scale = scale;
}

void ModelInstance::setMaterial(Material material) {
	m_material = material;
}

void ModelInstance::setModel(ModelAsset modelAsset) {
    m_model = &modelAsset;
}

glm::vec3 ModelInstance::getPosition() {
	return m_position;
}

glm::fquat ModelInstance::getOrientation() {
	return m_orientation;
}

glm::vec3 ModelInstance::getScale() {
	return m_scale;
}

Material ModelInstance::getMaterial() {
	return m_material;
}

ModelAsset ModelInstance::getModel() {
    return *m_model;
}

glm::mat4 ModelInstance::translation() {
	return glm::translate(glm::mat4(), m_position);
}

glm::mat4 ModelInstance::scale() {
	return glm::scale(glm::mat4(), m_scale);
}

glm::mat4 ModelInstance::rotation() {
	return glm::toMat4(m_orientation);
}

glm::mat4 ModelInstance::model() {
	return translation() * rotation() * scale();
}

void ModelInstance::render(Shader shader, ModelAsset modelAsset) {
	shader.use();

	GLint modelLoc = shader.getUniformLocation("model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model()));
	
	m_material.setUniforms(shader);

	if (m_model == NULL) {
		printf("ERROR: Can't render ModelInstance. ModelAsset not set.\n");
		exit(-1);
	}
	modelAsset.render();
}