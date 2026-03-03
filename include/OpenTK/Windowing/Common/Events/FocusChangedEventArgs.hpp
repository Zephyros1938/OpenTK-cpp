#pragma once

namespace OpenTK::Windowing::Common {
struct FocusChangedEventArgs {
  bool IsFocused;
  FocusChangedEventArgs(bool isFocused) : IsFocused(isFocused) {}
};
} // namespace OpenTK::windowing::common
