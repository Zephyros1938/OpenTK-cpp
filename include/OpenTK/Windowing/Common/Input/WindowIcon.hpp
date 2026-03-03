#pragma once

#include <OpenTK/Windowing/Common/Input/Image.hpp>

namespace OpenTK::windowing::common::input {
class WindowIcon {
  WindowIcon() {}

public:
  Image Images[];
  WindowIcon(Image *images) : Images(*images) {}
};
} // namespace OpenTK::windowing::common::input
