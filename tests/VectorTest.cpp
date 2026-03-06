#include "OpenTK/Mathematics/Vector.hpp"
#include "OpenTK/Mathematics/Matrix.hpp"
#include <iostream>
#include <ostream>

int main() {
  using namespace OpenTK::Mathematics;

  Vector2 a;

  Vector<64, bool> b;
  Vector<2, bool> b_s{true};
  b.SetSubVector(b_s, 1, 2);
  b.SetSubVectorI(b_s, std::vector{3, 4});
  Vector<2, bool> b2 = b.GetSubVector(1, 2);
  Matrix<4, 4, float> m = Matrix<4, 4, float>::Identity();

  std::cout << a << std::endl;
  std::cout << b << std::endl;
  std::cout << m << std::endl;
  std::cout << m.Determinant() << std::endl;
  std::cout << m.Identity() << std::endl;
  Matrix<3, 3, float> m2{2, 0, 0, 0, 2, 0, 0, 0, 2};
  Matrix<4, 4, float> m3(m2);
  std::cout << "m2: " << m2 << std::endl << "m3: " << m3 << std::endl;
  std::cout << "m COL0: " << m.GetColumn(0) << std::endl;
  std::cout << "m Clear: " << m.ClearTranslation() << std::endl;
  std::cout << "m scale: " << m3.ExtractScale() << std::endl;
  return 0;
}
