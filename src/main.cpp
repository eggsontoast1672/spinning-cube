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
    -0.5, -0.5,
     0.0,  0.5,
     0.5, -0.5,
  };

  GLuint vb;
  glGenBuffers(1, &vb);
  glBindBuffer(GL_ARRAY_BUFFER, vb);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  unsigned int indices[] = {
    0, 1, 2,
  };

  GLuint eb;
  glGenBuffers(1, &eb);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eb);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  Shader shader("res/shaders/basic.vert", "res/shaders/basic.frag");
  shader.bind();

  glEnableVertexAttribArray(0);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void *)0);

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

    // We want offset to oscillate between -0.5 and 0.5
    float offset_x = std::sin(glfwGetTime() * 2.0) * 0.5;
    shader.set_uniform("uniform_offset_x", offset_x);

    float offset_y = std::sin(glfwGetTime() * 1.0) * 0.5;
    shader.set_uniform("uniform_offset_y", offset_y);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
