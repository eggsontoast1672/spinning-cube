#pragma once

#include <initializer_list>
#include <vector>

#include <GL/glew.h>

class IndexBuffer
{
public:
    IndexBuffer(std::initializer_list<unsigned int> indices) noexcept;
    IndexBuffer(const IndexBuffer &) = delete;
    ~IndexBuffer() noexcept;

    IndexBuffer &operator=(const IndexBuffer &) = delete;

    void draw() const noexcept;

private:
    GLuint m_id;
    GLsizei m_count;
};
