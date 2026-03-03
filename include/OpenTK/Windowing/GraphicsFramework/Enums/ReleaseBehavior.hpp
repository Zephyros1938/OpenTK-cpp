#pragma once

#include <cstdint>

namespace OpenTK::Windowing::GraphicsFramework {
enum class ReleaseBehavior : int32_t {
  Any = 0,
  Flush = 0x00035001,
  None = 0x00035002
};
}
