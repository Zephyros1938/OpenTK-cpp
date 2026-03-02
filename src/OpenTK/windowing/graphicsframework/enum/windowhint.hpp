#pragma once

#include <cstdint>

namespace OpenTK {
namespace windowing {
namespace graphicsframework {
enum class WindowHintInt : uint32_t {
  PositionX = 0x0002000E,
  PositionY = 0x0002000F,
  ContextVersionMajor = 0x00022002,
  ContextVersionMinor = 0x00022003,
  ContextRevision = 0x00022004,
  RedBits = 0x00021001,
  GreenBits = 0x00021002,
  BlueBits = 0x00021003,
  AlphaBits = 0x00021004,
  DepthBits = 0x00021005,
  StencilBits = 0x00021006,
  AccumRedBits = 0x00021007,
  AccumGreenBits = 0x00021008,
  AccumBlueBits = 0x00021009,
  AccumAlphaBits = 0x0002100A,
  AuxBuffers = 0x0002100B,
  Samples = 0x0002100D,
  RefreshRate = 0x0002100F
};
}
} // namespace windowing

} // namespace OpenTK
