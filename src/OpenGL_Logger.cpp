#include "OpenGL_Logger.h"
#include "glfw3.h"
#include "Logger.h"
#include <iostream>

/*
 * Shader error log
 */
void printShaderLog(GLuint shader) {
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char*)malloc(len);
		glGetShaderInfoLog(shader, len, &chWrittn, log);
		Logger::LogPrint("Shader Info Log: %s", log);
		free(log);
	}
}

/*
 * Program error log
 */
void printProgramLog(int prog) {
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char*)malloc(len);
		glGetProgramInfoLog(prog, len, &chWrittn, log);
		Logger::LogPrint("Program Info Log: %s", log);
		free(log);
	}
}

/*
 * Determines if error
 */
bool checkOpenGLError() {
	bool foundError = false;
	int glErr = glGetError();
	while (glErr != GL_NO_ERROR) {
		Logger::LogPrint("glError: %d", glErr);
		foundError = true;
		glErr = glGetError();
	}
	return foundError;
}
