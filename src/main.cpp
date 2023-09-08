#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "error.hpp"
#include "index_buffer.hpp"
#include "shader.hpp"
#include "vertex.hpp"
#include "vertex_buffer.hpp"
#include "window.hpp"

int main()
{
    if (!glfwInit()) {
        throw std::runtime_error {"failed to initialize glfw"};
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Window window;

    if (glewInit() != GLEW_OK) {
        throw std::runtime_error {"failed to initialize glew"};
    }

    window.set_resize_callback([](GLFWwindow *window, int width, int height) {
        static_cast<void>(window);
        glCall(glViewport(0, 0, width, height));
    });

    glCall(glEnable(GL_DEPTH_TEST));

    VertexArray vertex_array;

    VertexBuffer vertex_buffer {
        // Top face
        Vertex {glm::vec3 {-0.5f, 0.5f, -0.5f}, glm::vec3 {1.0f, 1.0f, 1.0f}},
        Vertex {glm::vec3 {0.5f, 0.5f, -0.5f}, glm::vec3 {1.0f, 1.0f, 1.0f}},
        Vertex {glm::vec3 {-0.5f, 0.5f, 0.5f}, glm::vec3 {1.0f, 1.0f, 1.0f}},
        Vertex {glm::vec3 {0.5f, 0.5f, 0.5f}, glm::vec3 {1.0f, 1.0f, 1.0f}},

        // Left face
        Vertex {glm::vec3 {-0.5f, 0.5f, -0.5f}, glm::vec3 {1.0f, 0.5f, 0.0f}},
        Vertex {glm::vec3 {-0.5f, 0.5f, 0.5f}, glm::vec3 {1.0f, 0.5f, 0.0f}},
        Vertex {glm::vec3 {-0.5f, -0.5f, -0.5f}, glm::vec3 {1.0f, 0.5f, 0.0f}},
        Vertex {glm::vec3 {-0.5f, -0.5f, 0.5f}, glm::vec3 {1.0f, 0.5f, 0.0f}},

        // Front face
        Vertex {glm::vec3 {-0.5f, 0.5f, 0.5f}, glm::vec3 {0.0f, 1.0f, 0.0f}},
        Vertex {glm::vec3 {0.5f, 0.5f, 0.5f}, glm::vec3 {0.0f, 1.0f, 0.0f}},
        Vertex {glm::vec3 {-0.5f, -0.5f, 0.5f}, glm::vec3 {0.0f, 1.0f, 0.0f}},
        Vertex {glm::vec3 {0.5f, -0.5f, 0.5f}, glm::vec3 {0.0f, 1.0f, 0.0f}},

        // Right face
        Vertex {glm::vec3 {0.5f, 0.5f, 0.5f}, glm::vec3 {1.0f, 0.0f, 0.0f}},
        Vertex {glm::vec3 {0.5f, 0.5f, -0.5f}, glm::vec3 {1.0f, 0.0f, 0.0f}},
        Vertex {glm::vec3 {0.5f, -0.5f, 0.5f}, glm::vec3 {1.0f, 0.0f, 0.0f}},
        Vertex {glm::vec3 {0.5f, -0.5f, -0.5f}, glm::vec3 {1.0f, 0.0f, 0.0f}},

        // Back face
        Vertex {glm::vec3 {0.5f, 0.5f, -0.5f}, glm::vec3 {0.0f, 0.0f, 1.0f}},
        Vertex {glm::vec3 {-0.5f, 0.5f, -0.5f}, glm::vec3 {0.0f, 0.0f, 1.0f}},
        Vertex {glm::vec3 {0.5f, -0.5f, -0.5f}, glm::vec3 {0.0f, 0.0f, 1.0f}},
        Vertex {glm::vec3 {-0.5f, -0.5f, -0.5f}, glm::vec3 {0.0f, 0.0f, 1.0f}},

        // Bottom face
        Vertex {glm::vec3 {-0.5f, -0.5f, 0.5f}, glm::vec3 {1.0f, 1.0f, 0.0f}},
        Vertex {glm::vec3 {0.5f, -0.5f, 0.5f}, glm::vec3 {1.0f, 1.0f, 0.0f}},
        Vertex {glm::vec3 {-0.5f, -0.5f, -0.5f}, glm::vec3 {1.0f, 1.0f, 0.0f}},
        Vertex {glm::vec3 {0.5f, -0.5f, -0.5f}, glm::vec3 {1.0f, 1.0f, 0.0f}},
    };

    IndexBuffer index_buffer {
        0, 1, 2, 1, 2, 3,  // Top face
        4, 5, 6, 5, 6, 7,  // Left face
        8, 9, 10, 9, 10, 11,  // Front face
        12, 13, 14, 13, 14, 15,  // Right face
        16, 17, 18, 17, 18, 19,  // Back face
        20, 21, 22, 21, 22, 23,  // Bottom face
    };

    glCall(glEnableVertexAttribArray(0));
    glCall(glEnableVertexAttribArray(1));

    glCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position)));
    glCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color)));

    Shader shader {"res/shaders/basic.vert", "res/shaders/basic.frag"};

    glm::mat4 model;
    glm::mat4 view = glm::translate(glm::mat4 {1.0f}, glm::vec3 {0.0f, 0.0f, -3.0f});
    glm::mat4 projection;

    shader.set_uniform_mat4("u_view", view);

    while (!window.should_close()) {
        window.clear();

        model = glm::rotate(
            glm::mat4 {1.0f},
            static_cast<float>(glfwGetTime()),
            glm::vec3 {0.5f, 1.0f, 0.0f}
        );
        shader.set_uniform_mat4("u_model", model);

        glm::vec2 size = window.get_size();
        projection = glm::perspective(
            glm::radians(45.0f),
            size.x / size.y,
            0.1f,
            100.0f
        );
        shader.set_uniform_mat4("u_projection", projection);

        index_buffer.draw();
        window.display();
    }

    return 0;
}