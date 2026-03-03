#pragma once

#include <OpenTK/Windowing/GraphicsFramework/Enums/WindowHintRobustness.hpp>
#include <cstdint>

namespace OpenTK::windowing::graphicsframework {
enum class WindowAttributeGetRobustness : uint32_t {
  ContextRobustness =
      static_cast<uint32_t>(WindowHintRobustness::ContextRobustness)
};
}
