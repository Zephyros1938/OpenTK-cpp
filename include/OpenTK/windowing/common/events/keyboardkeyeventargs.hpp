#pragma once

#include <OpenTK/Ported/mods.hpp>
#include <OpenTK/windowing/graphicsframework/enum/keymodifiers.hpp>
#include <OpenTK/windowing/graphicsframework/enum/keys.hpp>

namespace OpenTK::windowing::common {
struct KeyboardKeyEventArgs {
  graphicsframework::Keys Key;
  int ScanCode;
  graphicsframework::KeyModifiers Modifiers;
  bool IsRepeat;
  bool Alt() const {
    return Ported::EnumUtil::HasFlag(Modifiers,
                                     graphicsframework::KeyModifiers::Alt);
  }
  bool Control() const {
    return Ported::EnumUtil::HasFlag(Modifiers,
                                     graphicsframework::KeyModifiers::Control);
  }
  bool Shift() const {
    return Ported::EnumUtil::HasFlag(Modifiers,
                                     graphicsframework::KeyModifiers::Shift);
  }
  bool Super() const {
    return Ported::EnumUtil::HasFlag(Modifiers,
                                     graphicsframework::KeyModifiers::Super);
  }
};
} // namespace OpenTK::windowing::common
