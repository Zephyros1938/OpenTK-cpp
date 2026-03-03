#pragma once

#include <OpenTK/Windowing/GraphicsFramework/Enums/WindowHintOpenGlProfile.hpp>
#include <cstdint>

namespace OpenTK::Windowing::GraphicsFramework {
enum class WindowAttributeGetOpenGlProfile : uint32_t {
  OpenGlProfile = static_cast<uint32_t>(WindowHintOpenGlProfile::OpenGlProfile)
};
}
