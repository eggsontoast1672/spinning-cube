#pragma once

#include <vector>

#include <glad/glad.h>

class VertexBuffer {
public:
    VertexBuffer() noexcept;
    VertexBuffer(const VertexBuffer &) = delete;
    VertexBuffer(VertexBuffer &&other) noexcept;
    ~VertexBuffer() noexcept;

    void bind() const noexcept;
    void set_data_binding(const std::vector<float> &data) const noexcept;

    VertexBuffer &operator=(const VertexBuffer &) = delete;
    VertexBuffer &operator=(VertexBuffer &&other) noexcept;

private:
    GLuint m_id;
};
