#include "vertex_array.hpp"

#include <GL/glew.h>

#include "error.hpp"

VertexArray::VertexArray() noexcept
{
    glCall(glGenVertexArrays(1, &m_id));
    glCall(glBindVertexArray(m_id));
}

VertexArray::~VertexArray() noexcept
{
    glCall(glDeleteVertexArrays(1, &m_id));
}
