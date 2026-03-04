#pragma once

#include <GLFW/glfw3.h>
#include <stdexcept>

namespace OpenTK::Windowing::Common::Input {
class Image {
public:
  int Width, Height;
  char *Data;
  Image(int width, int height, char *data) {
    if (data == NULL) {
      throw std::runtime_error("WINDOWING::COMMON::INPUT::IMAGE::NO_DATA");
    }

    if (sizeof(*data) < (unsigned int)(width * height * 4)) {
      throw std::runtime_error(
          "WINDOWING::COMMON::INPUT::IMAGE::SIZE_MISMATCH");
    }
    Width = width;
    Height = height;
    Data = data;
  }
  operator GLFWimage *() const {
    return new GLFWimage{this->Width, this->Height,
                         (unsigned char *)this->Data};
  }
  Image(GLFWimage glfwImage) {
    Width = glfwImage.width;
    Height = glfwImage.height;
    Data = (char *)glfwImage.pixels;
  }
};
} // namespace OpenTK::Windowing::Common::Input
