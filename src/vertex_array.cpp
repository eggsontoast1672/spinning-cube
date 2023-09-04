#include "vertex_array.hpp"

#include <utility>
#include <vector>

#include <GL/glew.h>

#include "error.hpp"

VertexArray::VertexArray() noexcept
: m_id {0} {
    glCall(glGenVertexArrays(1, &m_id));
}

VertexArray::VertexArray(VertexArray &&other) noexcept
: m_id {other.m_id}, m_indices {std::move(other.m_indices)}, m_vertices {std::move(other.m_vertices)} {
    other.m_id = 0;
}

VertexArray::~VertexArray() noexcept {
    if (m_id) {
        glCall(glDeleteVertexArrays(1, &m_id));
    }
}

void VertexArray::bind() const noexcept {
    glCall(glBindVertexArray(m_id));
}

void VertexArray::draw_binding() const noexcept {
    bind();
    m_indices.draw();
}

void VertexArray::set_indices_binding(const std::vector<unsigned int> &indices) noexcept {
    bind();
    m_indices.set_data_binding(indices);
}

void VertexArray::set_vertices_binding(const std::vector<float> &vertices) const noexcept {
    bind();
    m_vertices.set_data_binding(vertices);
}

VertexArray &VertexArray::operator=(VertexArray &&other) noexcept {
    if (this != &other) {
        if (m_id) {
            glCall(glDeleteVertexArrays(1, &m_id));
        }
        m_id = other.m_id;
        m_indices = std::move(other.m_indices);
        m_vertices = std::move(other.m_vertices);
        other.m_id = 0;
    }
    return *this;
}
