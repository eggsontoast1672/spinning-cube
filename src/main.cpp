#include <cstring>
#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "spinning-cube/shader.hpp"

static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  (void)window;
  glViewport(0, 0, width, height);
}

int main(int argc, char **argv) {
  std::string resource_path = get_resource_path(argc, argv);

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

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  GLuint va;

  glGenVertexArrays(1, &va);
  glBindVertexArray(va);

  float vertices[] = {
    -0.5,  0.5,
     0.5,  0.5,
    -0.5, -0.5,
     0.5, -0.5,
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

  std::string vertex_source = load_shader_source(resource_path + "/shaders/basic.vert");
  GLuint vertex_shader = create_shader(GL_VERTEX_SHADER, vertex_source.c_str());

  std::string fragment_source = load_shader_source(resource_path + "/shaders/basic.frag");
  GLuint fragment_shader = create_shader(GL_FRAGMENT_SHADER, fragment_source.c_str());

  GLuint program = create_program(vertex_shader, fragment_shader);
  glUseProgram(program);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

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

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
