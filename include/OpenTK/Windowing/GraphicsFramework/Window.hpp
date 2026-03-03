#pragma once

#include <GLFW/glfw3.h>
#include <stdexcept>

namespace OpenTK::Windowing::GraphicsFramework {
struct Window {
  GLFWwindow *handle;
  Window(GLFWwindow *w) : handle(w) {}
  operator GLFWwindow *() const {
    if (handle != nullptr) {
      return handle;
    }
    throw std::runtime_error("OpenTK::Windowing::GraphicsFramework::Window > "
                             "Window was null dereferencing!");
  }
};
} // namespace OpenTK::windowing::graphicsframework
