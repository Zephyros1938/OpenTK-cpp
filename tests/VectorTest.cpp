#include "OpenTK/Mathematics/Vector.hpp"
#include "OpenTK/Mathematics/Matrix.hpp"
#include <iostream>

int main() {
  using namespace OpenTK::Mathematics;

  Vector2 a;

  Vector<64, bool> b;
  Matrix<4, 4, float> m{};
  m.data[0][0] = 99;

  std::cout << a << std::endl;
  std::cout << b << std::endl;
  std::cout << m << std::endl;
  std::cout << m.Determinant() << std::endl;
  std::cout << m.Identity() << std::endl;

  return 0;
}
