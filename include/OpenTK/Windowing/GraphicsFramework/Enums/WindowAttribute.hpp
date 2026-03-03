#pragma once

#include <OpenTK/Windowing/GraphicsFramework/Enums/WindowHintBool.hpp>
namespace OpenTK::windowing::graphicsframework {
enum class WindowAttribute : uint32_t {
  Resizable = static_cast<uint32_t>(WindowHintBool::Resizable),
  Decorated = static_cast<uint32_t>(WindowHintBool::Decorated),
  AutoIconify = static_cast<uint32_t>(WindowHintBool::AutoIconify),
  Floating = static_cast<uint32_t>(WindowHintBool::Floating),
  FocusOnShow = static_cast<uint32_t>(WindowHintBool::FocusOnShow),
  MousePassthrough = static_cast<uint32_t>(WindowHintBool::MousePassthrough)
};
}
