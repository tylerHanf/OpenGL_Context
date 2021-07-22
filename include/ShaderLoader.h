#pragma once
#include <string>
#include "glew.h"

std::string readShaderSource(const char* filePath);
GLuint createShaderProgram(const char* vp, const char* fp);

