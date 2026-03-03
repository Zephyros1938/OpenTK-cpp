#pragma once

namespace OpenTK::Windowing::Common {
class IGraphicsContext {
public:
  virtual ~IGraphicsContext() = default;

  // Getters/Setters
  virtual bool IsCurrent() const = 0;
  virtual int GetSwapInterval() const = 0;
  virtual void SetSwapInterval(int interval) = 0;

  virtual void SwapBuffers() = 0;
  virtual void MakeCurrent() = 0;
  virtual void MakeNoneCurrent() = 0;
};
} // namespace OpenTK::windowing::common
