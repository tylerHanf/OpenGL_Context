#include "ShaderHandler.h"
#include "ShaderLoader.h"
#include "Logger.h"

void ShaderHandler::MakeProgramFromSource(const char* vert_filepath,
					  const char* frag_filepath,
					  const std::string programName)
{
  GLuint programID = createShaderProgram(vert_filepath, frag_filepath);
  ShaderProgram newProgram;
  newProgram.index = programID;
  programs[programName] = newProgram;

  // Add uniforms to the map if they don't already exist
  int numUniforms = 0;
  glGetProgramiv(programID, GL_ACTIVE_UNIFORMS, &numUniforms);

  const GLsizei bufSize = 256;
  GLchar name[bufSize];
  GLenum type;
  GLint act_size = 0;
  for (GLint i=0; i<numUniforms; ++i) {
    glGetActiveUniform(programID, i, bufSize, NULL, &act_size, &type, name);
    GL_Uniform uniform = {i, type};
    newProgram.uniforms.try_emplace(std::string(name), uniform);
  }
}

void ShaderHandler::MakeActive(std::string programName) {
  activeProgram = programs.at(programName).index;
  glUseProgram(activeProgram);
}
