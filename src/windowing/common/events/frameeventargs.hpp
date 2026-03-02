#pragma once

namespace windowing {
namespace common {
struct FrameEventArgs {
  double Time;
  FrameEventArgs(double elapsed) : Time(elapsed) {};
};
} // namespace common
} // namespace windowing
