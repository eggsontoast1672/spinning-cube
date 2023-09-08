#include "window.hpp"

#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "error.hpp"

Window::Window()
{
    m_handle = glfwCreateWindow(800, 600, "Spinning Cube", nullptr, nullptr);
    if (!m_handle) {
        glfwTerminate();
        throw std::runtime_error {"failed to create window"};
    }
    glfwMakeContextCurrent(m_handle);
}

Window::~Window() noexcept
{
    glfwTerminate();
}

void Window::clear() const noexcept
{
    glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Window::display() const noexcept
{
    glfwSwapBuffers(m_handle);
}

void Window::set_resize_callback(GLFWwindowsizefun callback) const noexcept
{
    glfwSetWindowSizeCallback(m_handle, callback);
}

bool Window::should_close() const noexcept
{
    glfwPollEvents();
    return glfwWindowShouldClose(m_handle);
}
