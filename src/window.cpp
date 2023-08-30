#include "window.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

Window::Window() {
    std::cout << "GLFW Version: " << glfwGetVersionString() << std::endl;

    glfwSetErrorCallback([](int code, const char *description) {
        std::cerr << "GLFW error: " << description << " (code " << code << ")"
                  << std::endl;
    });

    if (!glfwInit()) {
        throw std::runtime_error{"failed to initialize GLFW"};
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    handle = glfwCreateWindow(800, 600, "Spinning Cube", nullptr, nullptr);
    if (!handle) {
        throw std::runtime_error{"failed to create window"};
    }

    glfwMakeContextCurrent(handle);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error{"failed to initialize glad"};
    }
}

Window::~Window() {
    glfwTerminate();
}

bool Window::should_close() const {
    return glfwWindowShouldClose(handle);
}

void Window::swap_buffers() {
    glfwSwapBuffers(handle);
}