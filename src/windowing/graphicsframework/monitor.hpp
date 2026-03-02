#pragma once

#include <GLFW/glfw3.h>
namespace windowing {
namespace graphicsframework {
struct Monitor {
  GLFWmonitor *handle;
  Monitor(GLFWmonitor *h) : handle(h) {};
  operator GLFWmonitor *() { return handle; }
};
} // namespace graphicsframework
} // namespace windowing
