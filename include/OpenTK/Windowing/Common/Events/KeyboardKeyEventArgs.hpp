#pragma once

#include <OpenTK/Ported/EnumUtil.hpp>
#include <OpenTK/Windowing/GraphicsFramework/Enums/KeyModifiers.hpp>
#include <OpenTK/Windowing/GraphicsFramework/Enums/Keys.hpp>

namespace OpenTK::Windowing::Common {
struct KeyboardKeyEventArgs {
  GraphicsFramework::Keys Key;
  int ScanCode;
  GraphicsFramework::KeyModifiers Modifiers;
  bool IsRepeat;
  bool Alt() const {
    return Ported::EnumUtil::HasFlag(Modifiers,
                                     GraphicsFramework::KeyModifiers::Alt);
  }
  bool Control() const {
    return Ported::EnumUtil::HasFlag(Modifiers,
                                     GraphicsFramework::KeyModifiers::Control);
  }
  bool Shift() const {
    return Ported::EnumUtil::HasFlag(Modifiers,
                                     GraphicsFramework::KeyModifiers::Shift);
  }
  bool Super() const {
    return Ported::EnumUtil::HasFlag(Modifiers,
                                     GraphicsFramework::KeyModifiers::Super);
  }
};
} // namespace OpenTK::windowing::common
