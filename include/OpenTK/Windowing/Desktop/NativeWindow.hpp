#pragma once

#include "OpenTK/Ported/ConcurrentQueue.hpp"
#include "OpenTK/Windowing/Common/Input/MouseCursor.hpp"
#include "OpenTK/Windowing/GraphicsFramework/Cursor.hpp"
#include "OpenTK/Windowing/GraphicsFramework/GLFWCallbacks.hpp"
#include "OpenTK/Windowing/GraphicsFramework/Input/KeyboardState.hpp"
#include "OpenTK/Windowing/GraphicsFramework/Window.hpp"
#include <exception>
namespace OpenTK::Windowing::Desktop {
class NativeWindow {
  float _cachedWindowClientSize[2], _cachedWindowLocation[2],
      _lastReportedMousePos[2];
  const static Ported::ConcurrentQueue<std::exception_ptr> _callbackExceptions;
  windowing::graphicsframework::Cursor *_glfwCursor;
  windowing::common::input::MouseCursor _managedCursor =
      windowing::common::input::MouseCursor::Default();
  windowing::graphicsframework::KeyboardState KeyboardState =
      windowing::graphicsframework::KeyboardState();

public:
  windowing::graphicsframework::Window *WindowPtr;
};
} // namespace OpenTK::Windowing::Desktop
