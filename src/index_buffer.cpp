#include "index_buffer.hpp"

#include <vector>

#include <glad/glad.h>

#include "error.hpp"

IndexBuffer::IndexBuffer() noexcept
: m_id {0} {
    glCall(glGenBuffers(1, &m_id));
}

IndexBuffer::IndexBuffer(IndexBuffer &&other) noexcept
: m_id {other.m_id}, m_data {other.m_data} {
    other.m_id = 0;
}

IndexBuffer::~IndexBuffer() noexcept {
    if (m_id) {
        glCall(glDeleteBuffers(1, &m_id));
    }
}

void IndexBuffer::bind() const noexcept {
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
}

void IndexBuffer::draw() const noexcept {
    glCall(glDrawElements(GL_TRIANGLES, m_data.size(), GL_UNSIGNED_INT, nullptr));
}

void IndexBuffer::set_data_binding(const std::vector<unsigned int> &data) noexcept {
    bind();
    glCall(glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        data.size() * sizeof(unsigned int),
        data.data(),
        GL_STATIC_DRAW
    ));
    m_data = data;
}

IndexBuffer &IndexBuffer::operator=(IndexBuffer &&other) noexcept {
    if (this != &other) {
        if (m_id) {
            glCall(glDeleteBuffers(1, &m_id));
        }
        m_id = other.m_id;
        m_data = other.m_data;
        other.m_id = 0;
    }
    return *this;
}
