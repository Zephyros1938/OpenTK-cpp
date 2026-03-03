#pragma once

#include "OpenTK/Ported/Property.hpp"
#include "OpenTK/Windowing/Desktop/IGLFWGraphicsContext.hpp"
#include "OpenTK/Windowing/GraphicsFramework/GLFW.hpp"
#include "OpenTK/Windowing/GraphicsFramework/Window.hpp"
namespace OpenTK::Windowing::Desktop {
class GLFWGraphicsContext : IGLFWGraphicsContext {
  Windowing::GraphicsFramework::Window *_windowPtr;
  int _swapInterval;

public:
  GLFWGraphicsContext(Windowing::GraphicsFramework::Window *windowPtr)
      : _windowPtr(windowPtr), IGLFWGraphicsContext(windowPtr) {}
  bool IsCurrent() const {
    return Windowing::GraphicsFramework::GLFW::GetCurrentContext() ==
           _windowPtr;
  }
  Ported::Property<int> SwapInterval = Ported::Property<int>{
      [this]() { return _swapInterval; },
      [this](int v) {
        Windowing::GraphicsFramework::GLFW::SwapInterval(v);
        _swapInterval = v;
      }};
  void SwapBuffers() {
    Windowing::GraphicsFramework::GLFW::SwapBuffers(_windowPtr);
  }
  void MakeCurrent() {
    Windowing::GraphicsFramework::GLFW::MakeContextCurrent(_windowPtr);
  }
  void MakeNoneCurrent() {
    Windowing::GraphicsFramework::GLFW::MakeContextCurrent(NULL);
  }
};
} // namespace OpenTK::Windowing::Desktop
