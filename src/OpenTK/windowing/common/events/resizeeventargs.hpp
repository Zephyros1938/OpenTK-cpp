#pragma once

namespace OpenTK {

namespace windowing {
namespace common {
struct ResizeEventArgs {
  float Size[2];
  float Width() const { return Size[0]; }
  float Height() const { return Size[1]; }
  ResizeEventArgs(float size[2]) : Size(*size) {}
  ResizeEventArgs(float width, float height) : Size{width, height} {}
};
} // namespace common
} // namespace windowing

} // namespace OpenTK
