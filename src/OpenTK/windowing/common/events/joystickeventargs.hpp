#pragma once

namespace OpenTK {

namespace windowing {
namespace common {
struct JoystickEventArgs {
  int JoystickId;
  bool IsConnected;
  JoystickEventArgs(int joystickId, bool isConnected)
      : JoystickId(joystickId), IsConnected(isConnected) {}
};
} // namespace common
} // namespace windowing

} // namespace OpenTK
