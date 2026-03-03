#pragma once

namespace OpenTK {

namespace windowing {
namespace common {
struct MaximizedEventArgs {
  bool IsMaximized;
  MaximizedEventArgs(bool isMaximized) : IsMaximized(isMaximized) {}
};
} // namespace common
} // namespace windowing

} // namespace OpenTK
