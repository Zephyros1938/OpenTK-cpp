#pragma once

#include <cstdint>
namespace windowing {
namespace graphicsframework {
enum class ContextApi : int32_t {
  NativeContextApi = 0x00036001,
  EglContextApi = 0x00036002
};
}
} // namespace windowing
