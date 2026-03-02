#pragma once

#include "windowhintcontextapi.hpp"
#include <cstdint>
namespace windowing {
namespace graphicsframework {
enum class WindowAttributeGetContextApi : uint32_t {
  ContextCreationApi =
      static_cast<uint32_t>(WindowHintContextApi::ContextCreationApi)
};
}
} // namespace windowing
