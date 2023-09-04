#pragma once

#include <vector>

#include <GL/glew.h>

class IndexBuffer {
public:
    IndexBuffer() noexcept;
    IndexBuffer(const IndexBuffer &) = delete;
    IndexBuffer(IndexBuffer &&other) noexcept;
    ~IndexBuffer() noexcept;

    void bind() const noexcept;
    void draw() const noexcept;
    void set_data_binding(const std::vector<unsigned int> &data) noexcept;

    IndexBuffer &operator=(const IndexBuffer &) = delete;
    IndexBuffer &operator=(IndexBuffer &&other) noexcept;

private:
    GLuint m_id;
    std::vector<unsigned int> m_data;
};
