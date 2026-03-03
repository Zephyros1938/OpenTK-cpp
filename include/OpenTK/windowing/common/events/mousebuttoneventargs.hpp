#pragma once

#include <OpenTK/windowing/graphicsframework/enum/inputaction.hpp>
#include <OpenTK/windowing/graphicsframework/enum/keymodifiers.hpp>
#include <OpenTK/windowing/graphicsframework/enum/mousebutton.hpp>

namespace OpenTK::windowing::common {
struct MouseButtonEventArgs {
  graphicsframework::MouseButton _Button;
  graphicsframework::InputAction _Action;
  graphicsframework::KeyModifiers _Modifiers;
  graphicsframework::MouseButton Button() const { return _Button; }
  graphicsframework::InputAction Action() const { return _Action; }
  graphicsframework::KeyModifiers Modifiers() const { return _Modifiers; }
  bool IsPressed() const {
    return _Action != graphicsframework::InputAction::Release;
  }
  MouseButtonEventArgs(graphicsframework::MouseButton button,
                       graphicsframework::InputAction action,
                       graphicsframework::KeyModifiers modifiers)
      : _Button(button), _Action(action), _Modifiers(modifiers) {}
};
} // namespace OpenTK::windowing::common
