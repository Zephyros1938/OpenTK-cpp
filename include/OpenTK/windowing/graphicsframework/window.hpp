#pragma once

#include <GLFW/glfw3.h>

namespace OpenTK::windowing::graphicsframework {
struct Window {
  GLFWwindow *handle;
  Window(GLFWwindow *w) : handle(w) {}
  operator GLFWwindow *() const { return handle; }
};
} // namespace OpenTK::windowing::graphicsframework
