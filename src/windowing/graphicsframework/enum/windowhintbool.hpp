#pragma once

#include <cstdint>
namespace windowing {
namespace graphicsframework {
enum class WindowHintBool : uint32_t {
  Focused = 0x00020001,
  Iconified = 0x00020002,
  Resizable = 0x00020003,
  Visible = 0x00020004,
  Decorated = 0x00020005,
  AutoIconify = 0x00020006,
  Floating = 0x00020007,
  Maximized = 0x00020008,
  CenterCursor = 0x00020009,
  TransparentFramebuffer = 0x0002000A,
  Hovered = 0x0002000B,
  FocusOnShow = 0x0002000C,
  MousePassthrough = 0x0002000D,
  OpenGLForwardCompat = 0x00022006,
  OpenGLDebugContext = 0x00022007,
  ContextNoError = 0x0002200A,
  ScaleToMonitor = 0x0002200C,
  ScaleFramebuffer = 0x0002200D,
  CocoaRetinaFramebuffer = 0x00023001,
  CocoaGraphicsSwitching = 0x00023003,
  Win32KeyboardMenu = 0x00025001,
  Win32ShowDefault = 0x00025002,
  Stereo = 0x0002100C,
  DoubleBuffer = 0x00021010,
  SrgbCapable = 0x0002100E
};
}
} // namespace windowing
