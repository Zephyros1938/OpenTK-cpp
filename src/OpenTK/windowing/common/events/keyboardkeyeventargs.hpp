#pragma once

#include <core/mods.hpp>
#include "../../graphicsframework/enum/keymodifiers.hpp"
#include "../../graphicsframework/enum/keys.hpp"

namespace windowing {
namespace common {
struct KeyboardKeyEventArgs {
  graphicsframework::Keys Key;
  int ScanCode;
  graphicsframework::KeyModifiers Modifiers;
  bool IsRepeat;
  bool Alt() const {
    return core::enumutil::HasFlag(Modifiers,
                                   graphicsframework::KeyModifiers::Alt);
  }
  bool Control() const {
    return core::enumutil::HasFlag(Modifiers,
                                   graphicsframework::KeyModifiers::Control);
  }
  bool Shift() const {
    return core::enumutil::HasFlag(Modifiers,
                                   graphicsframework::KeyModifiers::Shift);
  }
  bool Super() const {
    return core::enumutil::HasFlag(Modifiers,
                                   graphicsframework::KeyModifiers::Super);
  }
};
} // namespace common
} // namespace windowing
