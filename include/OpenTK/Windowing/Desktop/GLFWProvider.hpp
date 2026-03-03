#pragma once

#include "OpenTK/Windowing/GraphicsFramework/Enums/ErrorCode.hpp"
#include "OpenTK/Windowing/GraphicsFramework/Enums/InitHintPlatform.hpp"
#include "OpenTK/Windowing/GraphicsFramework/Enums/Platform.hpp"
#include "OpenTK/Windowing/GraphicsFramework/GLFW.hpp"
#include "OpenTK/Windowing/GraphicsFramework/GLFWCallbacks.hpp"
#include "OpenTK/Windowing/GraphicsFramework/GLFWException.hpp"
#include <cstdlib>
#include <string>
#include <thread>
namespace OpenTK::Windowing::Desktop {
class GLFWProvider {

  static void
  DefaultErrorCallback(Windowing::GraphicsFramework::ErrorCode errorCode,
                       std::string description) {
    throw new Windowing::GraphicsFramework::GLFWException(
        "{description} (this is thrown from OpenTKs default GLFW error "
        "handler, if you find this exception inconvenient set your own error "
        "callback using GLFWProvider::SetErrorCallback)",
        errorCode);
  }
  static inline bool _initialized = false;
  static inline std::thread::id _mainThreadId;
  static inline Windowing::GraphicsFramework::GLFWCallbacks::ErrorCallback
      _errorCallback;

public:
  static inline bool CheckForMainThread = true;
  static inline bool HonorOpenTK4UseWayland = true;

  static void
  SetErrorCallback(Windowing::GraphicsFramework::GLFWCallbacks::ErrorCallback
                       errorCallback) {
    _errorCallback = errorCallback;
    Windowing::GraphicsFramework::GLFW::SetErrorCallback(_errorCallback);
  }
  static bool IsOnMainThread() {
    return CheckForMainThread == false ||
           _mainThreadId == std::this_thread::get_id();
  }

  static void EnsureInitialized() {
    if (CheckForMainThread) {

      if (_mainThreadId == std::thread::id()) {

        if (!_initialized) {
          _mainThreadId = std::this_thread::get_id();
        }
        if (std::this_thread::get_id() != _mainThreadId) {
          throw std::runtime_error(
              "GLFW can only be called from the main thread!");
        }
      }
    }
    if (!_initialized) {
#ifdef __linux__
      if (HonorOpenTK4UseWayland) {
        const char *sessionTypeEnv = std::getenv("XDG_SESSION_TYPE");
        const char *useWaylandEnv = std::getenv("OPENTK4_USE_WAYLAND");

        std::string sessionType = sessionTypeEnv ? sessionTypeEnv : "";
        std::string useWayland = useWaylandEnv ? useWaylandEnv : "";

        if (sessionType == "wayland" && useWayland == "0") {
          Windowing::GraphicsFramework::GLFW::InitHint(
              Windowing::GraphicsFramework::InitHintPlatform::Platform,
              Windowing::GraphicsFramework::Platform::X11);
        }
      }
#endif
      Windowing::GraphicsFramework::GLFW::SetErrorCallback(_errorCallback);
      Windowing::GraphicsFramework::GLFW::Init();
    }
  }
};
} // namespace OpenTK::Windowing::Desktop
