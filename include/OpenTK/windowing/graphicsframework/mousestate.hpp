#pragma once

#include "enum/mousebutton.hpp"
#include "window.hpp"
#include <GLFW/glfw3.h>
#include <bitset>
#include <cstring>

namespace OpenTK {
namespace windowing {
namespace graphicsframework {
class MouseState {
  const static int MaxButtons = 16;
  std::bitset<MaxButtons> _buttons;
  std::bitset<MaxButtons> _buttonsPrevious;

public:
  MouseState() {}
  MouseState(MouseState &source) {
    memcpy(&Position, source.Position, 2);
    memcpy(&PreviousPosition, source.PreviousPosition, 2);
    memcpy(&Scroll, source.Scroll, 2);
    memcpy(&PreviousScroll, source.PreviousScroll, 2);
    _buttons = source._buttons;
    _buttonsPrevious = source._buttonsPrevious;
  }
  float Position[2];
  float PreviousPosition[2];
  float *Delta() const {
    static float p[2] = {Position[0] - PreviousPosition[0],
                         Position[1] - PreviousPosition[1]};
    return p;
  }
  float Scroll[2];
  float PreviousScroll[2];
  float *ScrollDelta() const {
    static float p[2] = {Scroll[0] - PreviousScroll[0],
                         Scroll[1] - PreviousScroll[1]};
    return p;
  }
  bool operator[](MouseButton button) { return _buttons[(int)button]; }
  float X() { return Position[0]; }
  float Y() { return Position[1]; }
  float PreviousX() { return PreviousPosition[0]; }
  float PreviousY() { return PreviousPosition[1]; }
  bool IsAnyButtonDown() {
    for (size_t i = 0; i < MaxButtons; i++) {
      if (_buttons[i])
        return true;
    }
    return false;
  }
  void NewFrame(Window *windowPtr) {
    memset(&_buttonsPrevious, false, _buttonsPrevious.size());
    _buttonsPrevious |= _buttons;

    memcpy(&PreviousPosition, Position, 2);
    memcpy(&PreviousScroll, Scroll, 2);

    double x, y;
    glfwGetCursorPos(*windowPtr, &x, &y);
  }
};
} // namespace graphicsframework
} // namespace windowing

} // namespace OpenTK
