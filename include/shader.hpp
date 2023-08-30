#pragma once

#include <string>

#include <glad/glad.h>

class Shader {
public:
    Shader(GLuint vertex_shader, GLuint fragment_shader);
    ~Shader();

    void bind() const;

private:
    GLuint m_id;
};

GLuint create_shader(GLenum type, const char *source);
std::string load_shader_source(const std::string &path);