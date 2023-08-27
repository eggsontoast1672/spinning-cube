#include "spinning-cube/shader.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

#include <glad/glad.h>

static constexpr std::size_t LOG_SIZE = 512;

GLuint create_program(GLuint vertex_shader, GLuint fragment_shader) {
  GLuint program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  GLint status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (!status) {
    char log[LOG_SIZE];
    glGetProgramInfoLog(program, LOG_SIZE, nullptr, log);
    std::cerr << log << std::endl;
  }

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  return program;
}

GLuint create_shader(GLenum type, const char *source) {
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, nullptr);
  glCompileShader(shader);

  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (!status) {
    char log[LOG_SIZE];
    glGetShaderInfoLog(shader, LOG_SIZE, nullptr, log);
    std::cerr << log << std::endl;
  }

  return shader;
}

std::string get_resource_path(int argc, char **argv) {
  for (int i = 1; i < argc; ++i) {
    if (std::strcmp(argv[i], "--resource-path") == 0) {
      if (i + 1 >= argc) {
        std::cerr << "The path to the resource folder must be specified after --resource-path" << std::endl;
        return {};
      }
      return std::string{argv[i + 1]};
    }
  }
  std::cerr << "The resource path must be specified via the --resource-path flag" << std::endl;
  return {};
}

std::string load_shader_source(const std::string &path) {
  std::fstream stream{path};
  if (!stream.is_open()) {
    std::cerr << "Failed to open file '" << path << "'" << std::endl;
  }
  return std::string{
    std::istreambuf_iterator<char>{stream},
    std::istreambuf_iterator<char>{}
  };
}
