#pragma once

#include <cstdint>

namespace OpenTK {
namespace windowing {
namespace graphicsframework {
enum class ClientApi : int32_t {
  NoApi = 0,
  OpenGlApi = 0x00030001,
  OpenGlEsApi = 0x00030002
};
}
} // namespace windowing

} // namespace OpenTK
