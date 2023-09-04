#pragma once

#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader {
public:
    Shader(const std::string &vertex_path, const std::string &fragment_path);
    ~Shader() noexcept;

    void bind() const noexcept;
    void set_uniform_mat4(const std::string &name, const glm::mat4 &matrix) const noexcept;

private:
    GLuint m_id;

    static GLuint create_shader(GLenum type, const char *source);
    static std::string load_source(const std::string &path);
};
