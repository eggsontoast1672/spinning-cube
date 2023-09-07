#pragma once

#include <GLFW/glfw3.h>

#include "shader.hpp"
#include "vertex_array.hpp"

class Window {
public:
    Window();
    Window(const Window &) = delete;
    ~Window() noexcept;

    Window &operator=(const Window &) = delete;

    void clear() const noexcept;
    void display() const noexcept;
    void draw_binding(const VertexArray &vertex_array, const Shader &shader) const noexcept;
    bool should_close() const noexcept;

    static Window &instance() noexcept;

private:
    GLFWwindow *m_handle;
    VertexArray m_vertex_array;
};
