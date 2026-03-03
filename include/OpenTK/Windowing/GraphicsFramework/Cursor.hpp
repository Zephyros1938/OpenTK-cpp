#pragma once

#include <GLFW/glfw3.h>

namespace OpenTK::windowing::graphicsframework {
struct Cursor {
  GLFWcursor *handle;
  Cursor(GLFWcursor *i) : handle(i) {}

  operator GLFWcursor *() { return handle; }
};
} // namespace OpenTK::windowing::graphicsframework
