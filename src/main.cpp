#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "shader.hpp"
#include "vertex_array.hpp"
#include "window.hpp"

int main() {
    Window window;

    const VertexArray vertex_array;
    vertex_array.bind();

    float vertices[] = {
        -0.5f, 0.5f,  // v0
        0.5f, 0.5f,   // v1
        -0.5f, -0.5f, // v2
        0.5f, -0.5f,  // v3
    };

    vertex_array.add_vertex_buffer(sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int indices[] = {
        0, 1, 2, // t0
        1, 2, 3, // t1
    };

    vertex_array.add_index_buffer(sizeof(indices), indices, GL_STATIC_DRAW);

    std::string vertex_source = load_shader_source("res/shaders/basic.vert");
    std::string fragment_source = load_shader_source("res/shaders/basic.frag");

    GLuint vertex_shader = create_shader(GL_VERTEX_SHADER, vertex_source.c_str());
    GLuint fragment_shader = create_shader(GL_FRAGMENT_SHADER, fragment_source.c_str());

    Shader shader{vertex_shader, fragment_shader};

    vertex_array.add_layout(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void *)0);

    while (!window.should_close()) {
        glClear(GL_COLOR_BUFFER_BIT);

        vertex_array.bind();
        shader.bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        window.swap_buffers();

        glfwPollEvents();
    }

    return 0;
}