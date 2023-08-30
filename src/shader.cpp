#include "shader.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

#include <glad/glad.h>

#include "error.hpp"

Shader::Shader(GLuint vertex_shader, GLuint fragment_shader) {
    gl_check(m_id = glCreateProgram());
    gl_check(glAttachShader(m_id, vertex_shader));
    gl_check(glAttachShader(m_id, fragment_shader));
    gl_check(glLinkProgram(m_id));

    gl_check(glDeleteShader(vertex_shader));
    gl_check(glDeleteShader(fragment_shader));

    GLint status;
    gl_check(glGetProgramiv(m_id, GL_LINK_STATUS, &status));
    if (!status) {
        char buffer[512];
        gl_check(glGetProgramInfoLog(m_id, sizeof(buffer), nullptr, buffer));
        gl_check(glDeleteProgram(m_id));
        throw std::runtime_error{buffer};
    }
}

Shader::~Shader() {
    gl_check(glDeleteProgram(m_id));
}

void Shader::bind() const {
    gl_check(glUseProgram(m_id));
}

GLuint create_shader(GLenum type, const char *source) {
    GLuint shader;
    gl_check(shader = glCreateShader(type));
    gl_check(glShaderSource(shader, 1, &source, nullptr));
    gl_check(glCompileShader(shader));

    GLint status;
    gl_check(glGetShaderiv(shader, GL_COMPILE_STATUS, &status));
    if (!status) {
        char buffer[512];
        gl_check(glGetShaderInfoLog(shader, sizeof(buffer), nullptr, buffer));
        gl_check(glDeleteShader(shader));
        throw std::runtime_error{buffer};
    }

    return shader;
}

std::string load_shader_source(const std::string &path) {
    std::ifstream ifs{path};
    std::ostringstream oss;
    if (ifs.fail()) {
        oss << "failed to open file '" << path << "'";
        throw std::runtime_error(oss.str());
    }
    oss << ifs.rdbuf();
    return oss.str();
}