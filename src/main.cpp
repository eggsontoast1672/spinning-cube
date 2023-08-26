#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

constexpr std::size_t CREATE_PROGRAM_LOG_SIZE = 512;
constexpr std::size_t CREATE_SHADER_LOG_SIZE = 512;

static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  (void)window;

  glViewport(0, 0, width, height);
}

static std::string load_shader_source(const char *path) {
  std::ifstream stream{path};
  return std::string{
    std::istreambuf_iterator<char>{stream},
    std::istreambuf_iterator<char>{}
  };
}

static GLuint create_shader(GLenum type, const char *source) {
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, nullptr);
  glCompileShader(shader);

  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (!status) {
    char log[CREATE_SHADER_LOG_SIZE];
    glad_glGetShaderInfoLog(shader, CREATE_SHADER_LOG_SIZE, nullptr, log);

    const char *type_string;
    switch (type) {
    case GL_FRAGMENT_SHADER:
      type_string = "vertex";
      break;
    case GL_VERTEX_SHADER:
      type_string = "vertex";
      break;
    default:
      type_string = "undefined";
      break;
    }

    std::cerr << "Failed to create " << type_string << " shader: " << log << std::endl;
  }

  return shader;
}

static GLuint create_program(GLuint vertex_shader, GLuint fragment_shader) {
  GLuint program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  GLint status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (!status) {
    char log[CREATE_PROGRAM_LOG_SIZE];
    glGetProgramInfoLog(program, CREATE_PROGRAM_LOG_SIZE, nullptr, log);
    std::cerr << "Failed to create program: " << log << std::endl;
  }

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  return program;
}

int main() {
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
    -0.5, -0.5,
     0.0,  0.5,
     0.5, -0.5,
  };

  GLuint vb;

  glGenBuffers(1, &vb);
  glBindBuffer(GL_ARRAY_BUFFER, vb);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  std::string vertex_source = load_shader_source("res/shaders/basic.vert");
  GLuint vertex_shader = create_shader(GL_VERTEX_SHADER, vertex_source.c_str());

  std::string fragment_source = load_shader_source("res/shaders/basic.frag");
  GLuint fragment_shader = create_shader(GL_FRAGMENT_SHADER, fragment_source.c_str());

  GLuint program = create_program(vertex_shader, fragment_shader);
  glUseProgram(program);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

  while (!glfwWindowShouldClose(window)) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, true);
    }

    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
