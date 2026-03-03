#pragma once

#include <stdexcept>

namespace OpenTK::windowing::common::input {
class Image {
public:
  int Width, Height;
  char *Data;
  Image(int width, int height, char *data) {
    if (data == NULL) {
      throw std::runtime_error("WINDOWING::COMMON::INPUT::IMAGE::NO_DATA");
    }

    if (sizeof(data) < (unsigned int)(width * height * 4)) {
      throw std::runtime_error(
          "WINDOWING::COMMON::INPUT::IMAGE::SIZE_MISMATCH");
    }
    Width = width;
    Height = height;
    Data = data;
  }
};
} // namespace OpenTK::windowing::common::input
