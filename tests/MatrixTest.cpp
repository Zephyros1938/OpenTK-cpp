#include "OpenTK/Mathematics/Matrix.hpp"
#include <iostream>

int main() {
  using namespace OpenTK::Mathematics;

  Matrix<2, 2, float> m{1.f, 2.f, 3.f, 4.f};

  std::cout << m << std::endl;
  std::cout << m.Identity() << std::endl;

  return 0;
}
