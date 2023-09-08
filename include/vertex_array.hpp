#pragma once

#include <GL/glew.h>

class VertexArray
{
public:
    VertexArray() noexcept;
    VertexArray(const VertexArray &) = delete;
    ~VertexArray() noexcept;

    VertexArray &operator=(const VertexArray &) = delete;

private:
    GLuint m_id;
};
