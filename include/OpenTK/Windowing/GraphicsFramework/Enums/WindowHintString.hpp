#pragma once

#include <cstdint>

namespace OpenTK::Windowing::GraphicsFramework {
enum class WindowHintString : int32_t {
  CocoaFrameName = 0x00023002,
  X11ClassName = 0x00024001,
  X11InstanceName = 0x00024002,
  WaylandAppID = 0x00026001
};
}
