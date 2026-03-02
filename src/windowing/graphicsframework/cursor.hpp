#pragma once

#include <GLFW/glfw3.h>
namespace windowing {
namespace graphicsframework {
struct Cursor {
  GLFWcursor *handle;
  Cursor(GLFWcursor *i) : handle(i) {}

  operator GLFWcursor *() { return handle; }
};
} // namespace graphicsframework
} // namespace windowing
