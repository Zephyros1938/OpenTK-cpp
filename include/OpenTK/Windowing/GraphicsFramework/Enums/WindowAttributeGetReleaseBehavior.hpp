#pragma once

#include <OpenTK/Windowing/GraphicsFramework/Enums/WindowHintReleaseBehavior.hpp>
#include <cstdint>

namespace OpenTK::windowing::graphicsframework {
enum class WindowAttributeGetReleaseBehavior : uint32_t {
  ContextReleaseBehavior =
      static_cast<uint32_t>(WindowHintReleaseBehavior::ContextReleaseBehavior)
};
}
