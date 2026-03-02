#pragma once

namespace windowing {
namespace common {
struct FocusChangedEventArgs {
  bool IsFocused;
  FocusChangedEventArgs(bool isFocused) : IsFocused(isFocused) {}
};
} // namespace common
} // namespace windowing
