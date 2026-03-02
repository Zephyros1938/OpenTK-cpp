#pragma once

#include <cstdint>

namespace OpenTK {
namespace windowing {
namespace graphicsframework {
enum class KeyModifiers : uint32_t {
  Shift = 0x0001,
  Control = 0x0002,
  Alt = 0x0004,
  Super = 0x0008,
  CapsLock = 0x0010,
  NumLock = 0x0020
};

} // namespace graphicsframework
} // namespace windowing

} // namespace OpenTK
