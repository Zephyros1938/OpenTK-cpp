#pragma once
#include <GLFW/glfw3.h>
namespace windowing {
namespace graphicsframework {
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
} // namespace graphicsframework
} // namespace windowing
