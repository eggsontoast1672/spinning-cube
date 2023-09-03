#include "window.hpp"

#include <stdexcept>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "error.hpp"
#include "shader.hpp"
#include "vertex_array.hpp"

Window Window::s_instance;

Window::Window() {
    if (!glfwInit()) {
        throw std::runtime_error {"failed to initialize glfw"};
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_handle = glfwCreateWindow(800, 600, "Spinning Cube", nullptr, nullptr);
    if (!m_handle) {
        glfwTerminate();
        throw std::runtime_error {"failed to create window"};
    }

    glfwMakeContextCurrent(m_handle);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        throw std::runtime_error {"failed to initialize glad"};
    }

    glfwSetWindowSizeCallback(m_handle, [](GLFWwindow *window, int width, int height) {
        static_cast<void>(window);
        glCall(glViewport(0, 0, width, height));
    });

    glCall(glEnable(GL_DEPTH_TEST));
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

void Window::draw_binding(const VertexArray &vertex_array, const Shader &shader) const noexcept {
    shader.bind();
    vertex_array.draw_binding();
}

bool Window::should_close() const noexcept {
    glfwPollEvents();
    return glfwWindowShouldClose(m_handle);
}

Window &Window::instance() noexcept {
    return s_instance;
}
