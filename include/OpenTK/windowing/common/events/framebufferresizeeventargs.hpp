#pragma once

namespace OpenTK::windowing::common {
struct FramebufferResizeEventArgs {
  int Size[2];
  int Width() const { return Size[0]; }
  int Height() const { return Size[1]; }
  FramebufferResizeEventArgs(const int size[2]) : Size{*size} {}
  FramebufferResizeEventArgs(int width, int height) : Size{width, height} {}
};
} // namespace OpenTK::windowing::common
