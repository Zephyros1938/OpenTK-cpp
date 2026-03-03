#pragma once

#include <OpenTK/Windowing/GraphicsFramework/Enums/WindowHintBool.hpp>
#include <cstdint>

namespace OpenTK::windowing::graphicsframework {
enum class WindowAttributeGetBool : uint32_t {
  Focused = static_cast<uint32_t>(WindowHintBool::Focused),
  Iconified = static_cast<uint32_t>(WindowHintBool::Iconified),
  Resizable = static_cast<uint32_t>(WindowHintBool::Resizable),
  Visible = static_cast<uint32_t>(WindowHintBool::Visible),
  Decorated = static_cast<uint32_t>(WindowHintBool::Decorated),
  AutoIconify = static_cast<uint32_t>(WindowHintBool::AutoIconify),
  Floating = static_cast<uint32_t>(WindowHintBool::Floating),
  Maximized = static_cast<uint32_t>(WindowHintBool::Maximized),
  ContextNoError = static_cast<uint32_t>(WindowHintBool::ContextNoError),
  MousePassthrough = static_cast<uint32_t>(WindowHintBool::MousePassthrough),
  TransparentFramebuffer =
      static_cast<uint32_t>(WindowHintBool::TransparentFramebuffer),
  Hovered = static_cast<uint32_t>(WindowHintBool::Hovered),
  FocusOnShow = static_cast<uint32_t>(WindowHintBool::FocusOnShow),
  OpenGLForwardCompat =
      static_cast<uint32_t>(WindowHintBool::OpenGLForwardCompat),
  OpenGLDebugContext =
      static_cast<uint32_t>(WindowHintBool::OpenGLDebugContext),
  DoubleBuffer = static_cast<uint32_t>(WindowHintBool::DoubleBuffer)
};
}
