#pragma once

#include <cstdint>

namespace OpenTK::Windowing::GraphicsFramework {
enum class OpenGlProfile : int32_t {
  Any = 0,
  Core = 0x00032001,
  Compat = 0x00032002
};
}
