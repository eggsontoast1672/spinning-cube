#include "vertex_buffer.hpp"

#include <vector>

#include <glad/glad.h>

#include "error.hpp"

VertexBuffer::VertexBuffer() noexcept
: m_id {0} {
    glCall(glGenBuffers(1, &m_id));
}

VertexBuffer::VertexBuffer(VertexBuffer &&other) noexcept
: m_id {other.m_id} {
    other.m_id = 0;
}

VertexBuffer::~VertexBuffer() noexcept {
    if (m_id) {
        glCall(glDeleteBuffers(1, &m_id));
    }
}

void VertexBuffer::bind() const noexcept {
    glCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
}

void VertexBuffer::set_data_binding(const std::vector<float> &data) const noexcept {
    bind();
    glCall(glBufferData(
        GL_ARRAY_BUFFER,
        data.size() * sizeof(float),
        data.data(),
        GL_STATIC_DRAW
    ));
}

VertexBuffer &VertexBuffer::operator=(VertexBuffer &&other) noexcept {
    if (this != &other) {
        if (m_id) {
            glCall(glDeleteBuffers(1, &m_id));
        }
        m_id = other.m_id;
        other.m_id = 0;
    }
    return *this;
}
