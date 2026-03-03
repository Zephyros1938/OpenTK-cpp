#pragma once

#include <OpenTK/Windowing/GraphicsFramework/Enums/WindowHintClientApi.hpp>
#include <cstdint>

namespace OpenTK::windowing::graphicsframework {
enum class WindowAttributeGetClientApi : uint32_t {
  ClientApi = static_cast<uint32_t>(WindowHintClientApi::ClientApi)
};
}
