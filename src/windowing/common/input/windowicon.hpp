#pragma once

#include "image.hpp"

namespace windowing {
namespace common {
namespace input {
class WindowIcon {
  WindowIcon() {}

public:
  Image Images[];
  WindowIcon(Image *images) : Images(*images) {}
};
} // namespace input
} // namespace common
} // namespace windowing
