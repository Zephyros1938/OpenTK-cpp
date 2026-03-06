#pragma once

#include <array>
#include <cstddef>
#include <initializer_list>
#include <vector>

namespace OpenTK::Ported {

template <typename T> class IReadOnlyList {
public:
  virtual ~IReadOnlyList() = default;
  virtual size_t Count() const = 0;
  virtual const T &operator[](size_t index) const = 0;
  virtual typename std::vector<T>::const_iterator begin() const = 0;
  virtual typename std::vector<T>::const_iterator end() const = 0;
};

template <typename T> class ReadOnlyList : public IReadOnlyList<T> {
private:
  std::vector<T> _items;

public:
  explicit ReadOnlyList(std::vector<T> items) : _items(std::move(items)) {}
  ReadOnlyList(std::initializer_list<T> list) : _items(list) {}
  ReadOnlyList(const T *array, size_t count) : _items(array, array + count) {};
  template <size_t N>
  ReadOnlyList(const T (&arr)[N]) : _items(std::begin(arr), std::end(arr)) {}
  template <size_t N>
  ReadOnlyList(const std::array<T, N> *arr)
      : _items(arr->begin(), arr->end()){};
  template <size_t N>
  ReadOnlyList(const std::array<T, N> arr) : _items(arr.begin(), arr.end()){};
  size_t Count() const override { return _items.size(); }
  const T &operator[](size_t index) const override { return _items.at(index); }
  typename std::vector<T>::const_iterator begin() const override {
    return _items.begin();
  }
  typename std::vector<T>::const_iterator end() const override {
    return _items.end();
  }
};

} // namespace OpenTK::Ported
