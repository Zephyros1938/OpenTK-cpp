#pragma once

#include <OpenTK/Windowing/Common/Input/Image.hpp>
#include <iterator>
#include <vector>

namespace OpenTK::Windowing::Common::Input {
class WindowIcon {
  WindowIcon() {}

public:
  std::vector<Image> Images;
  template <size_t N> WindowIcon(Image images[N]) {
    for (size_t i = 0; i < N; ++i) {
      Images.push_back(images[i]);
    }
  }
};
} // namespace OpenTK::Windowing::Common::Input
