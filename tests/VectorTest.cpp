#include "OpenTK/Mathematics/Vector.hpp"
#include <assert.h>
#include <cstddef>
#include <iostream>
#include <ostream>

bool Near(float a, float b, float epsilon = 0.001f) {
  return std::abs(a - b) < epsilon;
}

int main() {
  using namespace OpenTK::Mathematics;
  std::cout << "Starting Vector tests..." << std::endl;

  // --- 1. Initialization ---
  Vector3 zero = Vector3::Zero();
  assert(zero.X() == 0.0f && zero.Y() == 0.0f && zero.Z() == 0.0f);

  Vector2 one = Vector2::One();
  assert(one[0] == 1.0f && one[1] == 1.0f);

  Vector3 custom(1.0f, 2.0f, 3.0f);
  assert(custom.X() == 1.0f);
  assert(custom.Y() == 2.0f);
  assert(custom.Z() == 3.0f);

  // --- 2. Arithmetic ---
  Vector3 a(10, 20, 30);
  Vector3 b(5, 5, 5);

  Vector3 sum = a + b;
  assert(sum.X() == 15.0f && sum.Z() == 35.0f);

  Vector3 diff = a - b;
  assert(diff.Y() == 15.0f);

  Vector3 scaled = a * 2.0f;
  assert(scaled.X() == 20.0f && scaled.Z() == 60.0f);

  // --- 3. Length and Normalization ---
  Vector3 v(3.0f, 0.0f, 4.0f); // 3-4-5 triangle
  assert(v.Length() == 5.0f);
  assert(v.LengthSquared() == 25.0f);

  Vector3 normalized = Vector3::Normalize(v);
  assert(Near(normalized.Length(), 1.0f));
  assert(Near(normalized.X(), 0.6f)); // 3/5

  // --- 4. Dot Product ---
  Vector3 v1(1, 0, 0);
  Vector3 v2(0, 1, 0);
  assert(Vector3::Dot(v1, v2) == 0.0f); // Orthogonal
  assert(Vector3::Dot(v1, v1) == 1.0f);

  // --- 5. Component Access & Swizzling Simulation ---
  Vector4 v4(1, 2, 3, 4);
  size_t indices[] = {2, 1, 0}; // Z, Y, X
  auto sub = v4.GetSubVector<3>(indices);
  assert(sub.X() == 3.0f && sub.Y() == 2.0f && sub.Z() == 1.0f);

  // --- 6. Interpolation (Lerp) ---
  Vector2 start(0, 0);
  Vector2 end(10, 10);
  Vector2 mid = Vector2::Lerp(start, end, 0.5f);
  assert(mid.X() == 5.0f && mid.Y() == 5.0f);

  // --- 7. Comparison Operators ---
  Vector2i i1(1, 5);
  Vector2i i2(2, 4);
  Vector<2, bool> result = (i1 < i2);
  assert(result[0] == true);  // 1 < 2
  assert(result[1] == false); // 5 < 4

  // --- 8. Printing ---
  std::cout << "Print test: " << custom << std::endl;

  std::cout << "All tests passed successfully!" << std::endl;
  return 0;
}
