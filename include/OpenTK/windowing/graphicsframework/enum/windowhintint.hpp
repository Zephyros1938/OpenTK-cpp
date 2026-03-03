#pragma once

#include "windowhint.hpp"
#include <cstdint>

namespace OpenTK {
namespace windowing {
namespace graphicsframework {
enum class WindowAttributeGetInt : uint32_t {
  ContextVersionMajor =
      static_cast<uint32_t>(WindowHintInt::ContextVersionMinor),
  ContextVersionMinor =
      static_cast<uint32_t>(WindowHintInt::ContextVersionMinor),
  ContextVersionRevision = static_cast<uint32_t>(WindowHintInt::ContextRevision)
};
}
} // namespace windowing

} // namespace OpenTK
