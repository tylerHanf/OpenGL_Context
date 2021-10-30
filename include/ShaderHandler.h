#include <map>
#include <string>
#include "glew.h"
#pragma once

struct GL_Uniform {
  GLuint index;
  GLenum type;
};

struct ShaderProgram {
  GLuint index;
  std::map<std::string, GL_Uniform> uniforms;
};

class ShaderHandler {
 public:
  void MakeProgramFromSource(const char* vert_filepath,
							 const char* frag_filepath,
							 const std::string programName); 

  void MakeActive(const std::string programName);
  ShaderProgram* GetShaderProgram(const std::string programName);
  
 private:
  GLuint activeProgram;
  std::map<std::string, ShaderProgram> programs;
};

static ShaderHandler shaderHandler;
