#pragma once

#include <cstdint>

namespace OpenTK {
namespace windowing {
namespace graphicsframework {
enum class Robustness : int32_t {
  NoRobustness = 0,
  NoResetNotification = 0x00031001,
  LoseContextOnReset = 0x00031002
};
}
} // namespace windowing

} // namespace OpenTK
