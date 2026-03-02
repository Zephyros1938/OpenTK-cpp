#pragma once

namespace OpenTK {

namespace windowing {
namespace common {
struct MinimizedEventArgs {
  bool IsMinimized;
  MinimizedEventArgs(bool isMinimized) : IsMinimized(isMinimized) {}
};
} // namespace common
} // namespace windowing

} // namespace OpenTK
