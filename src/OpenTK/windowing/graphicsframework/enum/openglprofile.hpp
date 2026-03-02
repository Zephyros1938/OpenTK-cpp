#pragma once

#include <cstdint>

namespace OpenTK {
namespace windowing {
namespace graphicsframework {
enum class OpenGlProfile : int32_t {
  Any = 0,
  Core = 0x00032001,
  Compat = 0x00032002
};
}
} // namespace windowing

} // namespace OpenTK
