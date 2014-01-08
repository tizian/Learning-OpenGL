#include "ModelAsset.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

ModelAsset::ModelAsset(Shader *shader, const char *filename){
	this->shader = shader;
	glGenVertexArrays(1, &vao);		// Generate a VAO
	glGenBuffers(1, &vbo);			// Generate a buffer object
	vertices = normals = uvs = colors = NULL;
	numVertices = numNormals = numUVs = numColors = 0;

	loadFromFile(filename);
}

ModelAsset::ModelAsset(Shader *shader) {
	this->shader = shader;
	glGenVertexArrays(1, &vao);		// Generate a VAO
	glGenBuffers(1, &vbo);			// Generate a buffer object
	vertices = normals = uvs = colors = NULL;
	numVertices = numNormals = numUVs = numColors = 0;
}

void ModelAsset::destroy() {
	glDisableVertexAttribArray(vPosition);
	glDisableVertexAttribArray(vNormal);
	glDisableVertexAttribArray(vTexCoord);
	glDisableVertexAttribArray(vColor);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

void ModelAsset::setGeometry(GLfloat *vertices, int size) {
	this->vertices = vertices;
	this->numVertices = size/sizeof(GLfloat)/3;
	vPosition = glGetAttribLocation(shader->getProgramID(), "vPosition");
}

void ModelAsset::setNormals(GLfloat *normals, int size) {
	this->normals = normals;
	this->numNormals = size/sizeof(GLfloat)/3;
	vNormal = glGetAttribLocation(shader->getProgramID(), "vNormal");
}

void ModelAsset::setVertexColors(GLfloat *colors, int size) {
	this->colors = colors;
	this->numColors = size/sizeof(GLfloat)/4;
	vColor = glGetAttribLocation(shader->getProgramID(), "vColor");
}

void ModelAsset::setTextureCoordinates(GLfloat *uvs, int size) {
	this->uvs = uvs;
	this->numUVs = size/sizeof(GLfloat)/2;
	vTexCoord = glGetAttribLocation(shader->getProgramID(), "vTexCoord");
}

void ModelAsset::loadVBO() {
	// Bind the vao
	glBindVertexArray(vao);

	// Bind the vbo as the current VBO.
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	int offset = 0;

	// Calculate the size of the buffer we need
	int sizeBuffer = (3*numVertices + 3*numNormals + 2*numUVs + 4*numColors) * sizeof(GLfloat);

	// Call glBufferData and tell the GPU how big the buffer is. We don't load the data yet.
	glBufferData(GL_ARRAY_BUFFER, sizeBuffer, NULL, GL_STATIC_DRAW);

	// If the vertices aren't NULL, load them onto the GPU. Offset is currently 0.
	if (vertices) {
		glBufferSubData(GL_ARRAY_BUFFER, offset, numVertices*3*sizeof(GLfloat), this->vertices);
		glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
		offset += numVertices*3*sizeof(GLfloat);
	}
	// Load in the vertex normals right after the vertex coordinates.
	if (normals) {
		glBufferSubData(GL_ARRAY_BUFFER, offset, numVertices*3*sizeof(GLfloat), this->normals);
		glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(offset));
		offset += numNormals*3*sizeof(GLfloat);
	}
	// Load in the texture coordinates right after the normals.
	if (uvs) {
		glBufferSubData(GL_ARRAY_BUFFER, offset, numUVs*2*sizeof(GLfloat), this->uvs);
		glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(offset));
		offset += numUVs*2*sizeof(GLfloat);
	}
	// Load in the color coordinates right after the texture coordinates.
	if (colors) {
		glBufferSubData(GL_ARRAY_BUFFER, offset, numColors*4*sizeof(GLfloat), this->colors);
		glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(offset));
		// offset += numColors*4*sizeof(GLfloat);
	}
}

void ModelAsset::render() {
	glBindVertexArray(vao);
    shader->use();

	if (vertices) {
		glEnableVertexAttribArray(vPosition);
	}
	if (normals) {
		glEnableVertexAttribArray(vNormal);
	}
	if (uvs) {
		glEnableVertexAttribArray(vTexCoord);
	}
	if (colors) {
		glEnableVertexAttribArray(vColor);
	}

	// Actual draw
	glDrawArrays(GL_TRIANGLES, 0, numVertices);

	if (vertices) {
		glDisableVertexAttribArray(vPosition);
	}
	if (normals) {
		glDisableVertexAttribArray(vNormal);
	}
	if (uvs) {
		glDisableVertexAttribArray(vTexCoord);
	}
	if (colors) {
		glDisableVertexAttribArray(vColor);
	}
}

void ModelAsset::loadFromFile(const char* filename) {
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(filename, aiProcessPreset_TargetRealtime_Fast);
	if (!scene) {
		printf("ERROR: reading mesh %s\n", filename);
		exit(-1);
	}

	aiMesh *mesh = scene->mMeshes[0];

	float *vertexArray;
	float *normalArray;
	float *uvArray;

	int numTriangles = mesh->mNumFaces*3;

	int numUvCoords = mesh->GetNumUVChannels();

	vertexArray = new float[numTriangles*3];
	normalArray = new float[numTriangles*3];
	if (numUvCoords > 0) {
		uvArray = new float[numTriangles*2];
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		const aiFace &face = mesh->mFaces[i];

		for (int j = 0; j < 3; j++) {
			if (numUvCoords > 0) {
				aiVector3D uv = mesh->mTextureCoords[0][face.mIndices[j]];
				memcpy(uvArray, &uv, sizeof(float)*2);
				uvArray += 2;
			}

			aiVector3D normal = mesh->mNormals[face.mIndices[j]];
			memcpy(normalArray, &normal, sizeof(float)*3);
			normalArray += 3;

			aiVector3D pos = mesh->mVertices[face.mIndices[j]];
			memcpy(vertexArray, &pos, sizeof(float)*3);
			vertexArray += 3;
		}
	}

	if (numUvCoords > 0) {
		uvArray -= numTriangles*2;
	}
	normalArray -= numTriangles*3;
	vertexArray -= numTriangles*3;

	setGeometry(vertexArray, numTriangles*3*sizeof(float));
	setNormals(normalArray, numTriangles*3*sizeof(float));
	if (numUvCoords > 0) {
		setTextureCoordinates(uvArray, numTriangles*2*sizeof(float));
	}

	loadVBO();
}