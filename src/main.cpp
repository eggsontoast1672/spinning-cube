#include <cmath>
#include <cstring>
#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "spinning-cube/shader.hpp"

int main(int argc, char **argv) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "Spinning Cube", nullptr, nullptr);
  if (!window) {
    std::cerr << "Failed to create window" << std::endl;
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD" << std::endl;

    // glfwTerminate closes any open GLFWwindows, so there's no need to worry
    // about closing them manually.
    glfwTerminate();
    return 1;
  }

  glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
  });

  GLuint va;

  glGenVertexArrays(1, &va);
  glBindVertexArray(va);

  // x, y, r, g, b
  float vertices[] = {
    -0.5,  0.5, 1.0, 0.0, 0.0,
     0.5,  0.5, 1.0, 1.0, 0.0,
    -0.5, -0.5, 0.0, 1.0, 0.0,
     0.5, -0.5, 0.0, 0.0, 1.0,
  };

  GLuint vb;
  glGenBuffers(1, &vb);
  glBindBuffer(GL_ARRAY_BUFFER, vb);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  unsigned int indices[] = {
    0, 1, 2,
    1, 2, 3,
  };

  GLuint eb;
  glGenBuffers(1, &eb);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eb);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  std::string vertex_source = load_shader_source("res/shaders/basic.vert");
  GLuint vertex_shader = create_shader(GL_VERTEX_SHADER, vertex_source.c_str());

  std::string fragment_source = load_shader_source("res/shaders/basic.frag");
  GLuint fragment_shader = create_shader(GL_FRAGMENT_SHADER, fragment_source.c_str());

  GLuint program = create_program(vertex_shader, fragment_shader);
  glUseProgram(program);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void *)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void *)(2 * sizeof(float)));

  for (int i = 1; i < argc; ++i) {
    if (std::strcmp(argv[i], "--wireframe") == 0) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
  }

  while (!glfwWindowShouldClose(window)) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, true);
    }

    glClear(GL_COLOR_BUFFER_BIT);

    float time = glfwGetTime();
    float green = (std::sin(time) / 2.0) + 0.5;
    GLint uniform_color = glGetUniformLocation(program, "uniform_color");
    glUniform4f(uniform_color, 0.0, green, 0.0, 1.0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
