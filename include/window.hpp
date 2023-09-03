#pragma once

#include <GLFW/glfw3.h>

#include "shader.hpp"
#include "vertex_array.hpp"

class Window {
private:
    static Window s_instance;

    Window();

public:
    Window(const Window &) = delete;
    Window(Window &&) = delete;
    ~Window() noexcept;

    void clear() const noexcept;
    void display() const noexcept;
    void draw_binding(const VertexArray &vertex_array, const Shader &shader) const noexcept;
    bool should_close() const noexcept;

    static Window &instance() noexcept;

    Window &operator=(const Window &) = delete;
    Window &operator=(Window &&) = delete;

private:
    GLFWwindow *m_handle;
};
