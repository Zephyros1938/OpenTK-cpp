#pragma once

#include <OpenTK/Windowing/GraphicsFramework/Image.hpp>
#include <iterator>
#include <vector>

namespace OpenTK::Windowing::Common::Input {
class WindowIcon {
  WindowIcon() {}

public:
  std::vector<GraphicsFramework::Image> Images;
  template <size_t N> WindowIcon(GraphicsFramework::Image images[N]) {
    for (size_t i = 0; i < N; ++i) {
      Images.push_back(images[i]);
    }
  }
};
} // namespace OpenTK::Windowing::Common::Input
