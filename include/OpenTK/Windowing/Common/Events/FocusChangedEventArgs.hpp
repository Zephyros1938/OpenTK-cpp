#pragma once

namespace OpenTK::windowing::common {
struct FocusChangedEventArgs {
  bool IsFocused;
  FocusChangedEventArgs(bool isFocused) : IsFocused(isFocused) {}
};
} // namespace OpenTK::windowing::common
