#pragma once
#include <GLFW/glfw3.h>
namespace windowing {
namespace graphicsframework {
struct GammaRamp {
public:
  unsigned short *Red, *Green, *Blue;
  unsigned int Size;
  GammaRamp() = default;

  // Conversion constructor
  GammaRamp(const GLFWgammaramp *mode)
      : Red(mode->red), Green(mode->green), Blue(mode->blue), Size(mode->size) {
  }
};
} // namespace graphicsframework
} // namespace windowing
