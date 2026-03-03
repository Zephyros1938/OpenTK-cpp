#pragma once

#include <mutex>
#include <queue>
#include <utility>
namespace OpenTK::Ported {
template <typename T> class ConcurrentQueue {
  std::queue<T> _queue;
  mutable std::mutex _mutex;

public:
  ConcurrentQueue() = default;

  void enqueue(T value) {
    std::lock_guard<std::mutex> lock(_mutex);
    _queue.push(std::move(value));
  }
  bool try_dequeue(T &outValue) {
    std::lock_guard<std::mutex> lock(_mutex);
    if (_queue.empty()) {
      return false;
    }
    outValue = std::move(_queue.front());
    _queue.pop();
    return true;
  }
  bool empty() const {
    std::lock_guard<std::mutex> lock(_mutex);
    return _queue.empty();
  }
};
} // namespace OpenTK::Ported
