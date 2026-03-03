#pragma once

namespace OpenTK::Windowing::Common {
struct ResizeEventArgs {
  float Size[2];
  float Width() const { return Size[0]; }
  float Height() const { return Size[1]; }
  ResizeEventArgs(float size[2]) : Size(*size) {}
  ResizeEventArgs(float width, float height) : Size{width, height} {}
};
} // namespace OpenTK::Windowing::Common
