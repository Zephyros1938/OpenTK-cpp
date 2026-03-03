#pragma once

#include <GLFW/glfw3.h>
#include <stdexcept>

namespace OpenTK::Windowing::GraphicsFramework {
struct Monitor {
  GLFWmonitor *handle;
  Monitor(GLFWmonitor *h) : handle(h) {};
  operator GLFWmonitor *() {
    if (handle != nullptr) {
      return handle;
    }
    throw std::runtime_error("OpenTK::Windowing::GraphicsFramework::Monitor > "
                             "Monitor was null while derefencing!");
  }
};
} // namespace OpenTK::windowing::graphicsframework
