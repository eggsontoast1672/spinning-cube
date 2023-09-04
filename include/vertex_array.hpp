#pragma once

#include <vector>

#include <GL/glew.h>

#include "index_buffer.hpp"
#include "vertex_buffer.hpp"

class VertexArray {
public:
    VertexArray() noexcept;
    VertexArray(const VertexArray &) = delete;
    VertexArray(VertexArray &&other) noexcept;
    ~VertexArray() noexcept;

    void bind() const noexcept;
    void draw_binding() const noexcept;
    void set_indices_binding(const std::vector<unsigned int> &indices) noexcept;
    void set_vertices_binding(const std::vector<float> &vertices) const noexcept;

    VertexArray &operator=(const VertexArray &) = delete;
    VertexArray &operator=(VertexArray &&other) noexcept;

private:
    GLuint m_id;
    IndexBuffer m_indices;
    VertexBuffer m_vertices;
};
