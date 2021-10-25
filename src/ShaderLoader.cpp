#include "ShaderLoader.h"
#include "glfw3.h"
#include "OpenGL_Logger.h"
#include "Logger.h"

#include <iostream>
#include <fstream>
#include "Logger.h"

/*
 * Read in GLSL file
 */
std::string readShaderSource(const char* filePath) {
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);
	if (!fileStream.is_open()) {
	  Logger::LogPrint("readShaderSource: ERROR Failed to load file %s", filePath);
	}
	std::string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

/*
 * Makes shader program with vertex and fragment shader
 */
GLuint createShaderProgram(const char* vp, const char* fp) {

	//Vertex error
	GLint vertCompiled;
	//Fragment error
	GLint fragCompiled;
	//Linker error
	GLint linked;

	std::string vshaderSourceStr = readShaderSource(vp);
	std::string fshaderSourceStr = readShaderSource(fp);

	const char* vshaderSource = vshaderSourceStr.c_str();
	const char* fshaderSource = fshaderSourceStr.c_str();

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vShader, 1, &vshaderSource, NULL);
	glShaderSource(fShader, 1, &fshaderSource, NULL);

	//Compile vertex shader
	glCompileShader(vShader);

	//Check for vertex shader compilation error
	checkOpenGLError();
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
	if (vertCompiled != 1) {
		Logger::LogPrint("vertex compilation failed");
		printShaderLog(vShader);
	}

	//Compile fragment shader
	glCompileShader(fShader);
	checkOpenGLError();
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
	if (fragCompiled != 1) {
		std::cout << "fragment compilation failed" << std::endl;
		printShaderLog(fShader);
	}

	GLuint vfProgram = glCreateProgram();
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);
	glLinkProgram(vfProgram);

	//Link Errors
	checkOpenGLError();
	glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
	if (linked != 1) {
		std::cout << "Linking failed" << std::endl;
		printProgramLog(vfProgram);
	}
	return vfProgram;
}
