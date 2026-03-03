#pragma once

#include <cstdint>

namespace OpenTK::Windowing::GraphicsFramework {
enum class Robustness : int32_t {
  NoRobustness = 0,
  NoResetNotification = 0x00031001,
  LoseContextOnReset = 0x00031002
};
}
