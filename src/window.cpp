#include "window.hpp"

#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "error.hpp"
#include "shader.hpp"
#include "vertex_array.hpp"

// Window Window::s_instance;

Window::Window() {
    m_handle = glfwCreateWindow(800, 600, "Spinning Cube", nullptr, nullptr);
    if (!m_handle) {
        glfwTerminate();
        throw std::runtime_error {"failed to create window"};
    }
    glfwMakeContextCurrent(m_handle);
}

Window::~Window() noexcept {
    glfwTerminate();
}

void Window::clear() const noexcept {
    glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Window::display() const noexcept {
    glfwSwapBuffers(m_handle);
}

bool Window::should_close() const noexcept {
    glfwPollEvents();
    return glfwWindowShouldClose(m_handle);
}
