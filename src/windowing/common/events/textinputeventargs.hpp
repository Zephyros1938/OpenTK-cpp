#pragma once

#include <string>
namespace windowing {
namespace common {
struct TextInputEventArgs {
  int Unicode;
  std::string AsString() { return std::to_string(Unicode); }
  TextInputEventArgs(int unicode) : Unicode(unicode) {}
};
} // namespace common
} // namespace windowing
