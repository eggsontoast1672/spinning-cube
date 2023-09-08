#pragma once

#include <initializer_list>

#include <GL/glew.h>

#include "vertex.hpp"

class VertexBuffer
{
public:
    VertexBuffer(std::initializer_list<Vertex> vertices) noexcept;
    VertexBuffer(const VertexBuffer &) = delete;
    ~VertexBuffer() noexcept;

    VertexBuffer &operator=(const VertexBuffer &) = delete;

private:
    GLuint m_id;
};
