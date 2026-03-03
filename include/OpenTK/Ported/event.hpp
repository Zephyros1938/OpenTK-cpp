#pragma once

#include <functional>
#include <vector>
namespace OpenTK::Ported {

template <typename... Args> class Event {
  std::vector<std::function<void(Args...)>> listeners;

public:
  void add(std::function<void(Args...)> listener) {
    listeners.push_back(listener);
  }

  void operator()(Args... args) const {
    for (const auto &listener : listeners) {
      listener(args...);
    }
  }
};

} // namespace OpenTK::Ported
