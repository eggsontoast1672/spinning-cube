#include "vertex_array.hpp"

#include <glad/glad.h>

#include "error.hpp"

VertexArray::VertexArray() {
    gl_check(glGenVertexArrays(1, &m_id));
}

VertexArray::~VertexArray() {
    gl_check(glDeleteVertexArrays(1, &m_id));
}

void VertexArray::add_index_buffer(GLsizeiptr size, const void *data, GLenum usage) const {
    GLint binding;
    gl_check(glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &binding));

    bind();

    GLuint buffer;
    gl_check(glGenBuffers(1, &buffer));
    gl_check(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer));
    gl_check(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage));

    gl_check(glBindVertexArray(0));
    gl_check(glDeleteBuffers(1, &buffer));

    gl_check(glBindVertexArray(binding));
}

void VertexArray::add_layout(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) const {
    gl_check(glEnableVertexAttribArray(index));
    gl_check(glVertexAttribPointer(index, size, type, normalized, stride, pointer));
}

void VertexArray::add_vertex_buffer(GLsizeiptr size, const void *data, GLenum usage) const {
    GLint binding;
    gl_check(glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &binding));

    bind();

    GLuint buffer;
    gl_check(glGenBuffers(1, &buffer));
    gl_check(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    gl_check(glBufferData(GL_ARRAY_BUFFER, size, data, usage));

    gl_check(glBindVertexArray(0));
    gl_check(glDeleteBuffers(1, &buffer));

    gl_check(glBindVertexArray(binding));
}

void VertexArray::bind() const {
    gl_check(glBindVertexArray(m_id));
}
