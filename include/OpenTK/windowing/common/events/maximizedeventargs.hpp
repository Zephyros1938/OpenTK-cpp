#pragma once

namespace OpenTK::windowing::common {
struct MaximizedEventArgs {
  bool IsMaximized;
  MaximizedEventArgs(bool isMaximized) : IsMaximized(isMaximized) {}
};
} // namespace OpenTK::windowing::common
