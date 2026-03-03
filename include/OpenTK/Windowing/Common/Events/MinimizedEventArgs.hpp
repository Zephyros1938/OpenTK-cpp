#pragma once

namespace OpenTK::windowing::common {
struct MinimizedEventArgs {
  bool IsMinimized;
  MinimizedEventArgs(bool isMinimized) : IsMinimized(isMinimized) {}
};
} // namespace OpenTK::windowing::common
