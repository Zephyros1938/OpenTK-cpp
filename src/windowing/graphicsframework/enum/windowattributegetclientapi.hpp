#pragma once

#include "windowhintclientapi.hpp"
#include <cstdint>
namespace windowing {
namespace graphicsframework {
enum class WindowAttributeGetClientApi : uint32_t {
  ClientApi = static_cast<uint32_t>(WindowHintClientApi::ClientApi)
};
}
} // namespace windowing
