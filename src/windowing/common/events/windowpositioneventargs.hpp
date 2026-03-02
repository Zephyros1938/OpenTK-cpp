#pragma once

namespace windowing {
namespace common {
struct WindowPositionEventArgs {
  float Position[2];
  float X() const { return Position[0]; }
  float Y() const { return Position[1]; }
  WindowPositionEventArgs(float position[2]) : Position(*position) {}
  WindowPositionEventArgs(float x, float y) : Position{x, y} {}
};
} // namespace common
} // namespace windowing
