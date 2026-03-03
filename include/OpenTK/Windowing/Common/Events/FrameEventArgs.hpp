#pragma once

namespace OpenTK::Windowing::Common {
struct FrameEventArgs {
  double Time;
  FrameEventArgs(double elapsed) : Time(elapsed) {};
};
} // namespace OpenTK::windowing::common
