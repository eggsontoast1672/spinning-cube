#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "error.hpp"
#include "shader.hpp"
#include "vertex_array.hpp"
#include "window.hpp"

int main() {
    VertexArray vertex_array;

    vertex_array.set_vertices_binding({
        // Top face
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // v0
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f,  // v1
        -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,  // v2
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f,   // v3

        // Left face
        -0.5f, 0.5f, -0.5f, 1.0f, 0.5f, 0.0f,  // v4
        -0.5f, 0.5f, 0.5f, 1.0f, 0.5f, 0.0f,   // v5
        -0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.0f, // v6
        -0.5f, -0.5f, 0.5f, 1.0f, 0.5f, 0.0f,  // v7

        // Front face
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,  // v8
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,   // v9
        -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // v10
        0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,  // v11

        // Right face
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,   // v12
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  // v13
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,  // v14
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // v15

        // Back face
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,   // v16
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,  // v17
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,  // v18
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // v19

        // Bottom face
        -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f,  // v20
        0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f,   // v21
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, // v22
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,  // v23
    });

    vertex_array.set_indices_binding({
        0, 1, 2, 1, 2, 3,       // Top face
        4, 5, 6, 5, 6, 7,       // Left face
        8, 9, 10, 9, 10, 11,    // Front face
        12, 13, 14, 13, 14, 15, // Right face
        16, 17, 18, 17, 18, 19, // Back face
        20, 21, 22, 21, 22, 23, // Bottom face
    });

    glCall(glEnableVertexAttribArray(0));
    glCall(glEnableVertexAttribArray(1));

    glCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void *)0));
    glCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void *)(3 * sizeof(float))));

    Shader shader {"res/shaders/basic.vert", "res/shaders/basic.frag"};

    glm::mat4 model {1.0f};
    glm::mat4 view = glm::translate(glm::mat4 {1.0f}, glm::vec3 {0.0f, 0.0f, -3.0f});
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    shader.set_uniform_mat4("u_model", model);
    shader.set_uniform_mat4("u_view", view);
    shader.set_uniform_mat4("u_projection", projection);

    while (!Window::instance().should_close()) {
        Window::instance().clear();

        model = glm::rotate(glm::mat4 {1.0f}, static_cast<float>(glfwGetTime()), glm::vec3 {0.5f, 1.0f, 0.0f});
        shader.set_uniform_mat4("u_model", model);

        Window::instance().draw_binding(vertex_array, shader);
        Window::instance().display();
    }

    return 0;
}