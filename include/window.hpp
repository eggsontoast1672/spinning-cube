#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Window {
public:
  Window();
  ~Window();

  bool should_close() const;
  void swap_buffers();

private:
  GLFWwindow *handle;
};