#pragma once

#include "Shader.h"

// Handles loading and rendering of model assets. (Raw models without material, textures, transformations)

class ModelAsset
{
public:
	ModelAsset(Shader *shader, const char *filename);
	ModelAsset(Shader *shader);
	ModelAsset() {};

	void setGeometry(GLfloat *vertices, int size);
	void setNormals(GLfloat *normals, int size);
	void setVertexColors(GLfloat *colors, int size);
	void setTextureCoordinates(GLfloat *uvs, int size);

	void loadFromFile(const char *filename);
	void loadVBO();
	void render();

	void destroy();

private:
	Shader *shader;			// The shader object for this model
	GLfloat *vertices;		// x, y, z
	GLfloat *normals;		// vertex normals
	GLfloat *uvs;			// texture coordinates
	GLfloat *colors;		// vertex colors
	GLuint numVertices, numNormals, numUVs, numColors;

	GLuint vao;				// vertex array object
	GLuint vbo;				// vertex buffer object

	GLuint vPosition;		// reference to the variable "vPosition" in the shader
	GLuint vNormal;			// reference to the variable "vNormal" in the shader
	GLuint vTexCoord;		// reference to the variable "vTexCoord" in the shader
	GLuint vColor;			// reference to the variable "vColor" in the shader
};