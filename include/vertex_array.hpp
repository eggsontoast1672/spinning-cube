#pragma once

#include <glad/glad.h>

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void add_index_buffer(GLsizeiptr size, const void *data, GLenum usage) const;
    void add_layout(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) const;
    void add_vertex_buffer(GLsizeiptr size, const void *data, GLenum usage) const;
    void bind() const;

private:
    GLuint m_id;
};
