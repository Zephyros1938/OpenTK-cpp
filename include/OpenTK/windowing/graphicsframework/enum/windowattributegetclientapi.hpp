#pragma once

#include "windowhintclientapi.hpp"
#include <cstdint>

namespace OpenTK::windowing::graphicsframework {
enum class WindowAttributeGetClientApi : uint32_t {
  ClientApi = static_cast<uint32_t>(WindowHintClientApi::ClientApi)
};
}
