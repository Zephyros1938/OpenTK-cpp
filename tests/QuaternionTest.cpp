#include "OpenTK/Mathematics/Quaternion.hpp"
#include <iostream>

int main() {
  OpenTK::Mathematics::Quaternion<float> q =
      OpenTK::Mathematics::Quaternion<float>::Identity();
  OpenTK::Mathematics::Quaternion<float> q2 =
      OpenTK::Mathematics::Quaternion<float>::Identity();
  std::cout << q << std::endl;
  std::cout << q.ToAxisAngle() << std::endl;
  std::cout << q.Multiply(q, q2) << std::endl;
  return 0;
}
