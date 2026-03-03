#pragma once

#include <functional>

namespace OpenTK::Ported {

template <typename T> class Property {
private:
  std::function<T()> getter;
  std::function<void(T)> setter;

public:
  // Constructors
  Property(std::function<T()> g, std::function<void(T)> s)
      : getter(g), setter(s) {}

  // Overload the assignment operator to trigger the setter
  T operator=(const T &value) {
    setter(value);
    return value;
  }

  // Overload the type conversion operator to trigger the getter
  operator T() const { return getter(); }
};
} // namespace OpenTK::Ported
