#pragma once
#include <GLFW/glfw3.h>

namespace OpenTK::Windowing::GraphicsFramework {
struct Image {
public:
  int Width, Height;
  unsigned char *Pixels;
  Image(int width, int height, unsigned char *pixels)
      : Width(width), Height(height), Pixels(pixels) {}
  operator GLFWimage *() const {
    return new GLFWimage{this->Width, this->Height, this->Pixels};
  }
};
} // namespace OpenTK::windowing::graphicsframework
