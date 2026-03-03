#pragma once

namespace OpenTK::Windowing::Common {
struct MaximizedEventArgs {
  bool IsMaximized;
  MaximizedEventArgs(bool isMaximized) : IsMaximized(isMaximized) {}
};
} // namespace OpenTK::windowing::common
