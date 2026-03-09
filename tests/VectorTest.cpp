#include "OpenTK/Mathematics/Vector.hpp"
#include "OpenTK/Mathematics/Matrix.hpp"
#include <iostream>
#include <ostream>

int main() {
  using namespace OpenTK::Mathematics;

  Vector2 a;

  Vector<4, float> b{2, -2, 2, -2};
  Vector<2, float> b_s{1, 2};
  std::cout << Vector<4, float>::Normalize(b) << std::endl;

  return 0;
}
