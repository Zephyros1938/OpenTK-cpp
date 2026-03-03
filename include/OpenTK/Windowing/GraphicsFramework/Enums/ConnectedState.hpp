#pragma once
#include <cstdint>

namespace OpenTK::Windowing::GraphicsFramework {
enum class ConnectedState : uint32_t {
  Connected = 0x00040001,
  Disconnected = 0x00040002
};
}
