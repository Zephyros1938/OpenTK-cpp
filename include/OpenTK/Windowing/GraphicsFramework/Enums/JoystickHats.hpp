#pragma once

namespace OpenTK::windowing::graphicsframework {
enum class JoystickHats : char {
  Centered = 0,
  Up = 1,
  Right = 2,
  Down = 4,
  Left = 8,
  RightUp = Right | Up,
  RightDown = Right | Down,
  LeftUp = Left | Up,
  LeftDown = Left | Down
};
}
