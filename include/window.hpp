#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shader.hpp"
#include "vertex_array.hpp"

class Window
{
public:
    Window();
    Window(const Window &) = delete;
    ~Window() noexcept;

    Window &operator=(const Window &) = delete;

    void clear() const noexcept;
    void display() const noexcept;
    glm::vec2 get_size() const noexcept;
    void set_resize_callback(GLFWwindowsizefun callback) const noexcept;
    bool should_close() const noexcept;

private:
    GLFWwindow *m_handle;
};
