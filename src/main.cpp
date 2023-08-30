#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stb/stb_image.h>

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Spinning Cube", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
    }

    glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height) {
        static_cast<void>(window);
        glViewport(0, 0, width, height);
    });

    GLuint vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    float vertices[] = {
        -0.5f, 0.5f, -1.0f, 1.0f,   // v0
        0.5f, 0.5f, 1.0f, 1.0f,     // v1
        -0.5f, -0.5f, -1.0f, -1.0f, // v2
        0.5f, -0.5f, 1.0f, -1.0f,   // v3
    };

    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int indices[] = {
        0, 1, 2, // t0
        1, 2, 3, // t1
    };

    GLuint index_buffer;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    const char *vertex_source = R"glsl(
        #version 330 core

        layout (location = 0) in vec2 position;
        layout (location = 1) in vec2 tex_coord;

        out vec2 vertex_tex_coord;

        void main() {
            gl_Position = vec4(position, 0.0f, 1.0f);
            vertex_tex_coord = tex_coord;
        }
    )glsl";

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_source, nullptr);
    glCompileShader(vertex_shader);

    GLint vertex_status;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &vertex_status);
    if (!vertex_status) {
        char log[512];
        glGetShaderInfoLog(vertex_shader, sizeof(log), nullptr, log);
        std::cerr << log << std::endl;
    }

    const char *fragment_source = R"glsl(
        #version 330 core

        in vec2 vertex_tex_coord;

        out vec4 fragment_color;

        uniform sampler2D fragment_sampler;

        void main() {
            fragment_color = texture(fragment_sampler, vertex_tex_coord);
        }
    )glsl";

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_source, nullptr);
    glCompileShader(fragment_shader);

    GLint fragment_status;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &fragment_status);
    if (!fragment_status) {
        char log[512];
        glGetShaderInfoLog(fragment_shader, sizeof(log), nullptr, log);
        std::cerr << log << std::endl;
    }

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    GLint program_status;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &program_status);
    if (!program_status) {
        char log[512];
        glGetProgramInfoLog(shader_program, sizeof(log), nullptr, log);
        std::cerr << log << std::endl;
    }

    glUseProgram(shader_program);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void *)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void *)(2 * sizeof(float)));

    int width;
    int height;
    int channels;
    unsigned char *data = stbi_load("res/textures/container.jpg", &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Failed to load image" << std::endl;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    stbi_image_free(data);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shader_program);
    glDeleteBuffers(1, &index_buffer);
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteVertexArrays(1, &vertex_array);
    glfwTerminate();

    return 0;
}