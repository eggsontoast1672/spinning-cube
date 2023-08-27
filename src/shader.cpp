#include "spinning-cube/shader.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

#include <glad/glad.h>

#include "spinning-cube/types.hpp"

Shader::Shader(const char *vertex_path, const char *fragment_path) {
  std::string vertex_source = load_shader_source(vertex_path);
  std::string fragment_source = load_shader_source(fragment_path);

  uint vertex_shader = create_shader(GL_VERTEX_SHADER, vertex_source.c_str());
  uint fragment_shader = create_shader(GL_FRAGMENT_SHADER, fragment_source.c_str());

  m_id = create_program(vertex_shader, fragment_shader);

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}

void Shader::bind() const {
  glUseProgram(m_id);
}

void Shader::set_uniform(const char *name, float value) const {
  glUniform1f(glGetUniformLocation(m_id, name), value);
}

uint Shader::create_program(uint vertex_shader, uint fragment_shader) {
  uint program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  int status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (!status) {
    char log[log_size];
    glGetProgramInfoLog(program, log_size, nullptr, log);
    std::cerr << log << std::endl;
  }

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  return program;
}

uint Shader::create_shader(uint type, const char *source) {
  uint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, nullptr);
  glCompileShader(shader);

  int status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (!status) {
    char log[log_size];
    glGetShaderInfoLog(shader, log_size, nullptr, log);
    std::cerr << log << std::endl;
  }

  return shader;
}

std::string Shader::load_shader_source(const char *path) {
  std::fstream stream;
  stream.exceptions(std::fstream::badbit | std::fstream::failbit);
  try {
    stream.open(path);
  } catch (const std::ios_base::failure &error) {
    std::cerr << error.what() << std::endl;
  }
  return std::string{
    std::istreambuf_iterator<char>{stream},
    std::istreambuf_iterator<char>{}
  };
}
