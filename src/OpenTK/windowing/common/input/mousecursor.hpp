#pragma once

#include "image.hpp"
#include <stdexcept>

namespace OpenTK {
namespace windowing {
namespace common {
namespace input {

class MouseCursor : private Image {
  enum class StandardShape {
    CustomShape = 0,
    Arrow,
    IBeam,
    Crosshair,
    PointingHand,
    ResizeEW,
    ResizeNS,
    ResizeNWSE,
    ResizeNESW,
    ResizeAll,
    NotAllowed
  };

public:
  StandardShape Shape;
  int X, Y;
  static inline const MouseCursor &Default() {
    static MouseCursor c(StandardShape::Arrow);
    return c;
  }
  static inline const MouseCursor &IBeam() {
    static MouseCursor c(StandardShape::IBeam);
    return c;
  }
  static inline const MouseCursor &Crosshair() {
    static MouseCursor c(StandardShape::Crosshair);
    return c;
  }
  static inline const MouseCursor &PointingHand() {
    static MouseCursor c(StandardShape::PointingHand);
    return c;
  }
  static inline const MouseCursor &ResizeEW() {
    static MouseCursor c(StandardShape::ResizeEW);
    return c;
  }
  static inline const MouseCursor &ResizeNS() {
    static MouseCursor c(StandardShape::ResizeNS);
    return c;
  }
  static inline const MouseCursor &ResizeNWSE() {
    static MouseCursor c(StandardShape::ResizeNWSE);
    return c;
  }
  static inline const MouseCursor &ResizeNESW() {
    static MouseCursor c(StandardShape::ResizeNESW);
    return c;
  }
  static inline const MouseCursor &NotAllowed() {
    static MouseCursor c(StandardShape::NotAllowed);
    return c;
  }
  static inline const MouseCursor &Empty() {
    static MouseCursor c(0, 0, 16, 16, new char[16 * 16 * 4]);
    return c;
  }
  MouseCursor(int hotX, int hotY, int width, int height, char *data)
      : Image(width, height, data), Shape(StandardShape::CustomShape), X(hotX),
        Y(hotY) {
    if (hotX < 0 || hotX >= width || hotY < 0 || hotY >= height)
      throw std::runtime_error(
          "ERROR::WINDOWING::COMMON::INPUT::MOUSECURSOR::INVALID_DATA");
    X = hotX;
    Y = hotY;
  }

private:
  MouseCursor(StandardShape shape)
      : Image(0, 0, {}), Shape(shape), X(0), Y(0) {}
}; // namespace input
} // namespace input
} // namespace common
} // namespace windowing

} // namespace OpenTK
