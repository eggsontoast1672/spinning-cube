#include "shader.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "error.hpp"

Shader::Shader(const std::string &vertex_path, const std::string &fragment_path)
    : m_id {0}
{
    std::string vertex_source = load_source(vertex_path);
    std::string fragment_source = load_source(fragment_path);

    GLuint vertex_shader = create_shader(GL_VERTEX_SHADER, vertex_source.c_str());
    GLuint fragment_shader = create_shader(GL_FRAGMENT_SHADER, fragment_source.c_str());

    glCall(m_id = glCreateProgram());
    glCall(glAttachShader(m_id, vertex_shader));
    glCall(glAttachShader(m_id, fragment_shader));
    glCall(glLinkProgram(m_id));

    glCall(glDeleteShader(vertex_shader));
    glCall(glDeleteShader(fragment_shader));

    GLint status;
    glCall(glGetProgramiv(m_id, GL_LINK_STATUS, &status));
    if (!status) {
        char log[512];
        glCall(glGetProgramInfoLog(m_id, sizeof(log), nullptr, log));
        glCall(glDeleteProgram(m_id));
        throw std::runtime_error {log};
    }

    glCall(glUseProgram(m_id));
}

Shader::~Shader() noexcept
{
    glCall(glDeleteProgram(m_id));
}

void Shader::set_uniform_mat4(const std::string &name, const glm::mat4 &matrix) const noexcept
{
    GLint location;
    glCall(location = glGetUniformLocation(m_id, name.c_str()));
    glCall(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)));
}

GLuint Shader::create_shader(GLenum type, const char *source)
{
    GLuint shader;
    glCall(shader = glCreateShader(type));
    glCall(glShaderSource(shader, 1, &source, nullptr));
    glCall(glCompileShader(shader));

    GLint status;
    glCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &status));
    if (!status) {
        char log[512];
        glCall(glGetShaderInfoLog(shader, sizeof(log), nullptr, log));
        glCall(glDeleteShader(shader));
        throw std::runtime_error {log};
    }

    return shader;
}

std::string Shader::load_source(const std::string &path)
{
    std::ifstream ifs {path};
    std::ostringstream oss;
    if (ifs.fail()) {
        oss << "failed to open file '" << path << "'";
        throw std::runtime_error {oss.str()};
    }
    oss << ifs.rdbuf();
    return oss.str();
}
