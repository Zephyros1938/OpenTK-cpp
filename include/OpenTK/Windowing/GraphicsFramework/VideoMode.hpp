#pragma once
#include <GLFW/glfw3.h>

namespace OpenTK::windowing::graphicsframework {
struct VideoMode {
public:
  int Width, Height, RedBits, GreenBits, BlueBits, RefreshRate;
  VideoMode() = default;

  // Conversion constructor
  VideoMode(const GLFWvidmode *mode)
      : Width(mode->width), Height(mode->height), RedBits(mode->redBits),
        GreenBits(mode->greenBits), BlueBits(mode->blueBits),
        RefreshRate(mode->refreshRate) {}
};
} // namespace OpenTK::windowing::graphicsframework
