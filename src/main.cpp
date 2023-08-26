#include <cstdlib>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

constexpr std::size_t CREATE_SHADER_LOG_SIZE = 512;

static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  (void)window;

  glViewport(0, 0, width, height);
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

    // TODO: Display name of shader that failed to compile
    std::cerr << "Failed to create shader: " << log << '\n';
  }

  return shader;
}

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "Spinning Cube", nullptr, nullptr);
  if (!window) {
    std::cerr << "Failed to create window\n";
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD\n";

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

  const char *vertex_source = R"glsl(
    #version 330 core

    layout (location = 0) in vec2 position;

    void main() {
      gl_Position = vec4(position.x, position.y, 0.0, 1.0);
    }
  )glsl";

  GLuint vertex_shader = create_shader(GL_VERTEX_SHADER, vertex_source);

  const char *fragment_source = R"glsl(
    #version 330 core

    out vec4 color;

    void main() {
      color = vec4(1.0, 0.5, 0.2, 1.0);
    }
  )glsl";

  GLuint fragment_shader = create_shader(GL_FRAGMENT_SHADER, fragment_source);

  GLuint program = glCreateProgram();

  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  // TODO: Check for program link errors

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

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
