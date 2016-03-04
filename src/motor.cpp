#include <iostream>
#include <Eigen/Core>

#include <vahlen/vahlen.h>

const double kPi = 3.141592653589793238462643383279;

using Mat = vahlen::Matrix<double>;

int main() {
  // std::cout << vahlen::id<double>() << std::endl;

  Mat e1 = vahlen::E1<double>();
  Mat e2 = vahlen::E2<double>();
  Mat e3 = vahlen::E3<double>();
  Mat ni = vahlen::Ni<double>();
  Mat no = vahlen::No<double>();

  std::cout << e1 * e1 << std::endl;
  std::cout << std::endl;
  std::cout << e2 * e2 << std::endl;
  std::cout << std::endl;
  std::cout << e3 * e3 << std::endl;

  std::cout << "E12:" << std::endl;
  std::cout << std::endl;
  std::cout << e1 * e2 << std::endl;
  std::cout << std::endl;
  std::cout << e2 * e1 << std::endl;
  std::cout << std::endl;
  Mat e12 = e1 * e2;
  std::cout << vahlen::Reverse(e12) << std::endl;
  std::cout << std::endl;

  Mat x = 1.0 * e1 + 2.0 * e2 + 3.0 * e3;
  std::cout << x << std::endl;
  std::cout << std::endl;

  Mat point = x + 0.5 * x * x * ni + no;
  std::cout << point << std::endl;
  std::cout << std::endl;

  std::cout << vahlen::Point(x) << std::endl;
  std::cout << std::endl;

  double v[3] = {1.0, 2.0, 3.0};
  std::cout << vahlen::Point(x) << std::endl;
  std::cout << std::endl;

  double theta_half = kPi / 4.0;
  double r[4] = {cos(theta_half), -sin(theta_half), 0.0, 0.0};

  Mat rotor = vahlen::Rotor<double>(r);
  double t[4] = {1.0, -0.5, -1.0, -1.5};
  Mat translator = vahlen::Translator<double>(t);

  std::cout << translator * no * vahlen::Reverse(translator) << std::endl;

  return 0;
}
