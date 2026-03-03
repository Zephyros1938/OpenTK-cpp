#pragma once

namespace OpenTK::Windowing::Common {
struct JoystickEventArgs {
  int JoystickId;
  bool IsConnected;
  JoystickEventArgs(int joystickId, bool isConnected)
      : JoystickId(joystickId), IsConnected(isConnected) {}
};
} // namespace OpenTK::windowing::common
