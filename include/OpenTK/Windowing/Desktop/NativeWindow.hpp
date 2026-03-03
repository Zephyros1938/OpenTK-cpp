#pragma once

#include "OpenTK/Ported/ConcurrentQueue.hpp"
#include "OpenTK/Ported/IReadOnlyList.hpp"
#include "OpenTK/Ported/Property.hpp"
#include "OpenTK/Windowing/Common/Enums/ContextApi.hpp"
#include "OpenTK/Windowing/Common/Enums/ContextFlags.hpp"
#include "OpenTK/Windowing/Common/Enums/ContextProfile.hpp"
#include "OpenTK/Windowing/Common/Input/Image.hpp"
#include "OpenTK/Windowing/Common/Input/MouseCursor.hpp"
#include "OpenTK/Windowing/Common/Input/WindowIcon.hpp"
#include "OpenTK/Windowing/Common/Interfaces/IGraphicsContext.hpp"
#include "OpenTK/Windowing/Common/VSyncMode.hpp"
#include "OpenTK/Windowing/Desktop/GLFWGraphicsContext.hpp"
#include "OpenTK/Windowing/Desktop/IGLFWGraphicsContext.hpp"
#include "OpenTK/Windowing/GraphicsFramework/Cursor.hpp"
#include "OpenTK/Windowing/GraphicsFramework/Enums/WindowAttribute.hpp"
#include "OpenTK/Windowing/GraphicsFramework/GLFW.hpp"
#include "OpenTK/Windowing/GraphicsFramework/GLFWCallbacks.hpp"
#include "OpenTK/Windowing/GraphicsFramework/Input/JoystickState.hpp"
#include "OpenTK/Windowing/GraphicsFramework/Input/KeyboardState.hpp"
#include "OpenTK/Windowing/GraphicsFramework/Input/MouseState.hpp"
#include "OpenTK/Windowing/GraphicsFramework/Window.hpp"
#include <GLFW/glfw3.h>
#include <array>
#include <exception>
#include <memory>
#include <stdexcept>

namespace OpenTK::Windowing::Desktop {
using GLFW = Windowing::GraphicsFramework::GLFW;
template <typename T> using Property = Ported::Property<T>;
class NativeWindow {
  using _Cursor_ = GraphicsFramework::Cursor;
  using _MouseCursor_ = Common::Input::MouseCursor;
  using _KeyboardState_ = GraphicsFramework::KeyboardState;
  using _JoystickState_ = GraphicsFramework::JoystickState;
  using _Window_ = GraphicsFramework::Window;
  using _MouseState_ = GraphicsFramework::MouseState;
  using _VSyncMode_ = Common::VSyncMode;
  using _ContextAPI_ = Common::ContextAPI;
  using _ContextProfile_ = Common::ContextProfile;
  using _ContextFlags_ = Common::ContextFlags;
  using _IGLFWGraphicsContext_ = IGLFWGraphicsContext;
  using _GLFWGraphicsContext_ = GLFWGraphicsContext;
  using _WindowIcon_ = Common::Input::WindowIcon;
  using _Image_ = Common::Input::Image;

  float _cachedWindowClientSize[2], _cachedWindowLocation[2],
      _lastReportedMousePos[2];
  const static Ported::ConcurrentQueue<std::exception_ptr> _callbackExceptions;
  _Cursor_ *_glfwCursor;
  _MouseCursor_ _managedCursor = _MouseCursor_::Default();
  _KeyboardState_ KeyboardState = _KeyboardState_();
  std::array<_JoystickState_, 16> _joystickStates;
  _VSyncMode_ _vSync;
  bool _autoIconify;
  _WindowIcon_ _icon;

public:
  _Window_ *WindowPtr;
  _MouseState_ MouseState = _MouseState_();

  _ContextAPI_ API;
  _ContextProfile_ Profile;
  _ContextFlags_ Flags;
  std::unique_ptr<_IGLFWGraphicsContext_> Context;

  const Ported::ReadOnlyList<_JoystickState_> JoystickStates() {
    return &_joystickStates;
  }
  Property<float *> MousePosition{[this]() { return _lastReportedMousePos; },
                                  [this](float value[2]) {
                                    memcpy(this->_lastReportedMousePos, value,
                                           sizeof(*value));
                                  }};

  bool IsAnyKeyDown() { return KeyboardState.IsAnyKeyDown(); }
  bool IsAnyMouseButtonDown() { return MouseState.IsAnyButtonDown(); }
  Property<_VSyncMode_> VSync{
      [this]() {
        if (Context == NULL)
          throw std::runtime_error(
              "Cannot control VSync when running with ContextAPI::NoAPI");
        return _vSync;
      },
      [this](_VSyncMode_ value) {
        if (Context == NULL)
          throw new std::runtime_error(
              "Cannot control VSync when running with ContextAPI::NoAPI");
        auto *isContext = dynamic_cast<_GLFWGraphicsContext_ *>(Context.get());
        if (!isContext) {
          throw std::runtime_error("Could not obtain GLFWGraphicsContext");
        } else {
          switch (value) {
          case (_VSyncMode_::On):
            isContext->SwapInterval = 1;
          case (_VSyncMode_::Off):
            isContext->SwapInterval = 0;
          }
          _vSync = value;
        }
      }};
  Property<bool> AutoIconify{
      [this]() { return _autoIconify; },
      [this](bool value) {
        if (_autoIconify != value) {
          _autoIconify = value;
          GLFW::SetWindowAttrib(WindowPtr,
                                GraphicsFramework::WindowAttribute::AutoIconify,
                                value);
        }
      }};
  Property<_WindowIcon_> Icon{
      [this]() { return _icon; },
      [this](_WindowIcon_ value) { // INFO : no weird GChandle stuff is needed
                                   // here since C++'s garbage collector works
                                   // differently than C#'s
        const auto &images = value.Images;
        int count = images.size();
        if (count > 0) {
          GLFWimage *glfwImages =
              (GLFWimage *)alloca(count * sizeof(GLFWimage));
          for (int i = 0; i < count; i++) {
            const _Image_ &src = images[i];

            glfwImages[i].width = src.Width;
            glfwImages[i].height = src.Height;
            glfwImages[i].pixels = (unsigned char *)src.Data;
          }
          ReadOnlySpan<_Image_> imageSpan{glfwImages};
          GLFW::SetWindowIcon(this->WindowPtr, glfwImages);
        }
      }};
};
} // namespace OpenTK::Windowing::Desktop
