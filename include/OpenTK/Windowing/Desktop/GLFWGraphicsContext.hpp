#pragma once

#include "OpenTK/Ported/Property.hpp"
#include "OpenTK/Windowing/Desktop/IGLFWGraphicsContext.hpp"
#include "OpenTK/Windowing/GraphicsFramework/GLFW.hpp"
#include "OpenTK/Windowing/GraphicsFramework/Window.hpp"
namespace OpenTK::Windowing::Desktop {
class GLFWGraphicsContext : IGLFWGraphicsContext {
  windowing::graphicsframework::Window *_windowPtr;
  int _swapInterval;

public:
  GLFWGraphicsContext(windowing::graphicsframework::Window *windowPtr)
      : _windowPtr(windowPtr) {}
  bool IsCurrent() const {
    return windowing::graphicsframework::GLFW::GetCurrentContext() ==
           _windowPtr;
  }
  Ported::Property<int> SwapInterval = Ported::Property<int>{
      [this]() { return _swapInterval; },
      [this](int v) {
        windowing::graphicsframework::GLFW::SwapInterval(v);
        _swapInterval = v;
      }};
  void SwapBuffers() {
    windowing::graphicsframework::GLFW::SwapBuffers(_windowPtr);
  }
  void MakeCurrent() {
    windowing::graphicsframework::GLFW::MakeContextCurrent(_windowPtr);
  }
  void MakeNoneCurrent() {
    windowing::graphicsframework::GLFW::MakeContextCurrent(NULL);
  }
};
} // namespace OpenTK::Windowing::Desktop
