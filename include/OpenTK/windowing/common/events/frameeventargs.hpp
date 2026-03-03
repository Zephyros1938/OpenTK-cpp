#pragma once

namespace OpenTK::windowing::common {
struct FrameEventArgs {
  double Time;
  FrameEventArgs(double elapsed) : Time(elapsed) {};
};
} // namespace OpenTK::windowing::common
