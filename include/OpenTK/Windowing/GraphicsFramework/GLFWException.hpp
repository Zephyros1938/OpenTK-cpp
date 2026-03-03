#pragma once

#include "OpenTK/Windowing/GraphicsFramework/Enums/ErrorCode.hpp"
#include <GLFW/glfw3.h>
#include <exception>
#include <stdexcept>

namespace OpenTK::windowing::graphicsframework {
class GLFWException : std::runtime_error {
public:
  ErrorCode ErrorCode;
  GLFWException()
      : std::runtime_error("OpenTK::Windowing::GraphicsFramework::"
                           "GLFWException > Default GLFW Error") {}
  GLFWException(const std::string &message, enum ErrorCode errorCode)
      : ErrorCode(errorCode), std::runtime_error(message) {}
  explicit GLFWException(const std::string &message)
      : ErrorCode(ErrorCode::NoError), std::runtime_error(message) {}
};
} // namespace OpenTK::windowing::graphicsframework
