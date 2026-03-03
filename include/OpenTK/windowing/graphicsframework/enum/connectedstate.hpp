#pragma once
#include <cstdint>

namespace OpenTK {
namespace windowing {
namespace graphicsframework {
enum class ConnectedState : uint32_t {
  Connected = 0x00040001,
  Disconnected = 0x00040002
};
}
} // namespace windowing

} // namespace OpenTK
