#pragma once

#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>

class Shader
{
public:
	Shader() {};
	Shader(const char *vertexShaderPath, const char *fragmentShaderPath);

	GLint programID;

	GLint getAttribLocation(const char *name) const;
	GLint getUniformLocation(const char *name) const;

	void use();

	void destroy();

private:
	char *readFile(const char* filename);
	bool compiledStatus(GLint shaderID);
	bool linkedStatus(GLint programID);

	GLint compileShader(char *shaderSource, GLenum shaderType);
	GLint linkShaderProgram(GLint vertexShaderID, GLint fragmentShaderID);
};