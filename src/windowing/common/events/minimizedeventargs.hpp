#pragma once

namespace windowing {
namespace common {
struct MinimizedEventArgs {
  bool IsMinimized;
  MinimizedEventArgs(bool isMinimized) : IsMinimized(isMinimized) {}
};
} // namespace common
} // namespace windowing
