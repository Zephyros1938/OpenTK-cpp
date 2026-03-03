#pragma once

namespace OpenTK::Windowing::Common {
struct MouseMoveEventArgs {
  float Position[2], Delta[2];
  float X() const { return Position[0]; }
  float Y() const { return Position[1]; }
  float DeltaX() const { return Delta[0]; }
  float DeltaY() const { return Delta[1]; }
  MouseMoveEventArgs(float position[2], float delta[2])
      : Position(*position), Delta(*delta) {}
  MouseMoveEventArgs(float x, float y, float deltaX, float deltaY)
      : Position{x, y}, Delta{deltaX, deltaY} {}
};
} // namespace OpenTK::windowing::common
