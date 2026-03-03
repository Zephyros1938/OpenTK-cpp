#pragma once

namespace OpenTK::windowing::common {
struct MouseWheelEventArgs {
  float Offset[2];
  float OffsetX() const { return Offset[0]; }
  float OffsetY() const { return Offset[1]; }
  MouseWheelEventArgs(float offset[2]) : Offset(*offset) {}
  MouseWheelEventArgs(float offsetX, float offsetY)
      : Offset{offsetX, offsetY} {}
};
} // namespace OpenTK::windowing::common
