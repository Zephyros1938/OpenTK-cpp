#pragma once

#include <stdexcept>
namespace windowing {
namespace common {
namespace input {
class Image {
public:
  int Width, Height;
  char *Data;
  Image(int width, int height, char *data) {
    if (data == NULL) {
      throw std::runtime_error("WINDOWING::COMMON::INPUT::IMAGE::NO_DATA");
    }

    if (sizeof(data) < width * height * 4) {
      throw std::runtime_error(
          "WINDOWING::COMMON::INPUT::IMAGE::SIZE_MISMATCH");
    }
    Width = width;
    Height = height;
    Data = data;
  }
};
} // namespace input
} // namespace common
} // namespace windowing
