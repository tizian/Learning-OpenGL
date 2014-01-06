#include "Shader.h"


Shader::Shader(const char *vertexShaderPath, const char *fragmentShaderPath) {
	char *vertexCode = readFile(vertexShaderPath);
	char *fragmentCode = readFile(fragmentShaderPath);

	if (!(vertexCode && fragmentCode)) {
		printf("Can't find shader file\n");
		exit(-1);
	}
	GLint vertexID = compileShader(vertexCode, GL_VERTEX_SHADER);
	GLint fragmentID = compileShader(fragmentCode, GL_FRAGMENT_SHADER);

	programID = linkShaderProgram(vertexID, fragmentID);
	delete(vertexCode);
	delete(fragmentCode);
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
}

char *Shader::readFile(const char* filename) {
	FILE *fp = fopen(filename, "r");

	fseek(fp, 0, SEEK_END);
	long file_length = ftell(fp);

	fseek(fp, 0, SEEK_SET);
	char *contents = new char[file_length+1];
	for (int i = 0; i < file_length+1; i++) {
		contents[i] = 0;
	}
	fread(contents, 1, file_length, fp);
	contents[file_length] = '\0';
	fclose(fp);

	return contents;
}

bool Shader::compiledStatus(GLint shaderID) {
	GLint compiled = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);
	if (compiled) {
		return true;
	}
	else {
		GLint logLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
		char *msgBuffer = new char[logLength];
		glGetShaderInfoLog(shaderID, logLength, NULL, msgBuffer);
		printf("%s\n", msgBuffer);
		delete(msgBuffer);
		return false;
	}
}

GLint Shader::compileShader(char *shaderSource, GLenum shaderType) {
	GLint shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, (const GLchar**)&shaderSource, NULL);
	glCompileShader(shaderID);
	bool compiledCorrectly = compiledStatus(shaderID);
	if (compiledCorrectly) {
		return shaderID;
	}
	return -1;
}

bool Shader::linkedStatus(GLint programID) {
	GLint linked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, &linked);
	if (linked) {
		return true;
	}
	else {
		GLint logLength;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);
		char *msgBuffer = new char[logLength];
		glGetProgramInfoLog(programID, logLength, NULL, msgBuffer);
		printf("%s\n", msgBuffer);
		delete(msgBuffer);
		return false;
	}
}

GLint Shader::linkShaderProgram(GLint vertexShaderID, GLint fragmentShaderID) {
	GLint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	bool linked = linkedStatus(programID);

	if (linked) {
		return programID;
	}
	return -1;
}

GLint Shader::getAttribLocation(const char *name) const {
	if (!name) {
		printf("Could not find attrib location: Invalid name.\n");
		exit(-1);
	}

	GLint attrib = glGetAttribLocation(programID, name);
	if (attrib == -1) {
		printf("Could not get attrib location with name: %s.\n", name);
		exit(-1);
	}
	return attrib;
}

GLint Shader::getUniformLocation(const char *name) const {
	if (!name) {
		printf("Could not find uniform location: Invalid name.\n");
		exit(-1);
	}

	GLint uniform = glGetUniformLocation(programID, name);
	if (uniform == -1) {
		printf("Could not get uniform location with name: %s.\n", name);
		exit(-1);
	}
	return uniform;
}

void Shader::use() {
	glUseProgram(programID);
}

void Shader::destroy(void) {
	glDeleteProgram(programID);
}
