#pragma once

#include <OpenTK/Windowing/GraphicsFramework/Enums/InputAction.hpp>
#include <OpenTK/Windowing/GraphicsFramework/Enums/KeyModifiers.hpp>
#include <OpenTK/Windowing/GraphicsFramework/Enums/Keys.hpp>
#include <OpenTK/Windowing/GraphicsFramework/Enums/MouseButton.hpp>

namespace OpenTK::Windowing::Common {
struct MouseButtonEventArgs {
  GraphicsFramework::MouseButton _Button;
  GraphicsFramework::InputAction _Action;
  GraphicsFramework::KeyModifiers _Modifiers;
  GraphicsFramework::MouseButton Button() const { return _Button; }
  GraphicsFramework::InputAction Action() const { return _Action; }
  GraphicsFramework::KeyModifiers Modifiers() const { return _Modifiers; }
  bool IsPressed() const {
    return _Action != GraphicsFramework::InputAction::Release;
  }
  MouseButtonEventArgs(GraphicsFramework::MouseButton button,
                       GraphicsFramework::InputAction action,
                       GraphicsFramework::KeyModifiers modifiers)
      : _Button(button), _Action(action), _Modifiers(modifiers) {}
};
} // namespace OpenTK::windowing::common
