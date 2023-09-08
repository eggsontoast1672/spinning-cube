#include "index_buffer.hpp"

#include <initializer_list>
#include <vector>

#include <GL/glew.h>

#include "error.hpp"

IndexBuffer::IndexBuffer(std::initializer_list<unsigned int> indices) noexcept
    : m_count {static_cast<GLsizei>(indices.size())}
{
    const std::vector<unsigned int> indices_vector {indices};

    glCall(glGenBuffers(1, &m_id));
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
    glCall(glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indices_vector.size() * sizeof(unsigned int),
        indices_vector.data(),
        GL_STATIC_DRAW
    ));
}

IndexBuffer::~IndexBuffer() noexcept
{
    glCall(glDeleteBuffers(1, &m_id));
}

void IndexBuffer::draw() const noexcept
{
    glCall(glDrawElements(GL_TRIANGLES, m_count, GL_UNSIGNED_INT, nullptr));
}
