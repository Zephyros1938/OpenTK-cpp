#pragma once

#include <GLFW/glfw3.h>

namespace OpenTK::windowing::graphicsframework {
struct Monitor {
  GLFWmonitor *handle;
  Monitor(GLFWmonitor *h) : handle(h) {};
  operator GLFWmonitor *() { return handle; }
};
} // namespace OpenTK::windowing::graphicsframework
