#include "vertex_buffer.hpp"

#include <initializer_list>
#include <vector>

#include <GL/glew.h>

#include "error.hpp"

VertexBuffer::VertexBuffer(std::initializer_list<Vertex> vertices) noexcept
{
    const std::vector<Vertex> vertices_vector {vertices};

    glCall(glGenBuffers(1, &m_id));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
    glCall(glBufferData(
        GL_ARRAY_BUFFER,
        vertices_vector.size() * sizeof(Vertex),
        vertices_vector.data(),
        GL_STATIC_DRAW
    ));
}

VertexBuffer::~VertexBuffer() noexcept
{
    glCall(glDeleteBuffers(1, &m_id));
}
