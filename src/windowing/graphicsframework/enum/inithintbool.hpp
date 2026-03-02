#pragma once

#include <cstdint>
namespace windowing {
namespace graphicsframework {
enum class InitHintBool : uint32_t {
  JoystickHatButtons = 0x00050001,
  CocoaChdirResources = 0x00051001,
  CocoaMenubar = 0x00051002,
  X11XcbVulkanSurface = 0x00052001
};
}
} // namespace windowing
