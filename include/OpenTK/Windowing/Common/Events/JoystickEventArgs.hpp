#pragma once

namespace OpenTK::windowing::common {
struct JoystickEventArgs {
  int JoystickId;
  bool IsConnected;
  JoystickEventArgs(int joystickId, bool isConnected)
      : JoystickId(joystickId), IsConnected(isConnected) {}
};
} // namespace OpenTK::windowing::common
