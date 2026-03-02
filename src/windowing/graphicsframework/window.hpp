#pragma once

#include <GLFW/glfw3.h>
namespace windowing {
namespace graphicsframework {
struct Window {
  GLFWwindow *handle;
  Window(GLFWwindow *w) : handle(w) {}
  operator GLFWwindow *() const { return handle; }
};
} // namespace graphicsframework
} // namespace windowing
