#pragma once

#include <cstdint>

#include <OpenTK/Windowing/GraphicsFramework/Enums/WindowHintContextApi.hpp>

namespace OpenTK::Windowing::GraphicsFramework {
enum class WindowAttributeGetContextApi : uint32_t {
  ContextCreationApi =
      static_cast<uint32_t>(WindowHintContextApi::ContextCreationApi)
};
}
