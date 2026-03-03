#pragma once

#include <cstdint>

namespace OpenTK::Windowing::GraphicsFramework {
enum class ClientApi : int32_t {
  NoApi = 0,
  OpenGlApi = 0x00030001,
  OpenGlEsApi = 0x00030002
};
}
