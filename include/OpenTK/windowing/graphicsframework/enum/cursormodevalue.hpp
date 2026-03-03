#pragma once

#include <cstdint>

namespace OpenTK {
namespace windowing {
namespace graphicsframework {
enum class CursorModeValue : int {
  CursorNormal = 0x00034001,
  CursorHidden = 0x00034002,
  CursorDisabled = 0x00034003,
  CursorCaptured = 0x00034004

};
}
} // namespace windowing

} // namespace OpenTK
