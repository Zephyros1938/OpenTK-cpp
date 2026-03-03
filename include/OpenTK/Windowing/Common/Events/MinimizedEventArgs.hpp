#pragma once

namespace OpenTK::Windowing::Common {
struct MinimizedEventArgs {
  bool IsMinimized;
  MinimizedEventArgs(bool isMinimized) : IsMinimized(isMinimized) {}
};
} // namespace OpenTK::windowing::common
