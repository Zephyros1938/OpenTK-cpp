#pragma once

#include <string>

namespace OpenTK::Windowing::Common {
struct TextInputEventArgs {
  int Unicode;
  std::string AsString() { return std::to_string(Unicode); }
  TextInputEventArgs(int unicode) : Unicode(unicode) {}
};
} // namespace OpenTK::windowing::common
