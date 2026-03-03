#pragma once

#include <cstdint>

namespace OpenTK::windowing::graphicsframework {
enum class MouseButton : uint32_t {
  Button1 = 0,
  Button2,
  Button3,
  Button4,
  Button5,
  Button6,
  Button7,
  Button8,
  Left = Button1,
  Right = Button2,
  Middle = Button3,
  Last = Button8
};
}
