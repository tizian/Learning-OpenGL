#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>

#include <stdio.h>
#include <stdlib.h>

class Shader
{
public:
	Shader() {};
	Shader(const char *vertexShaderPath, const char *fragmentShaderPath);

	GLint getAttribute(const char *name) const;
    
    void setUniform(const char *name, float x, float y, float z);
    void setUniform(const char *name, const glm::vec3 v);
    void setUniform(const char *name, const glm::vec4 v);
    void setUniform(const char *name, const glm::mat3 m);
    void setUniform(const char *name, const glm::mat4 m);
    void setUniform(const char *name, float val);
    void setUniform(const char *name, int val);
    void setUniform(const char *name, bool val);
    
    GLint getProgramID() const;

	void use();

	void destroy();

private:
	char *readFile(const char* filename);
	bool compiledStatus(GLint shaderID);
	bool linkedStatus(GLint programID);

	GLint compileShader(char *shaderSource, GLenum shaderType);
	GLint linkShaderProgram(GLint vertexShaderID, GLint fragmentShaderID);
    
    GLint getUniform(const char *name) const;
    
    GLint m_programID;
};