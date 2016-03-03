#include <iostream>
#include <Eigen/Core>

#include <vahlen/vahlen.h>

int main() {
  // std::cout << vahlen::id<double>() << std::endl;

  std::cout << vahlen::E1<double>() << std::endl;
  std::cout << std::endl;
  std::cout << vahlen::E2<double>() << std::endl;
  std::cout << std::endl;
  std::cout << vahlen::E3<double>() << std::endl;
  std::cout << std::endl;
  // std::cout << vahlen::No<double>() << std::endl;
  // std::cout << std::endl;
  // std::cout << vahlen::Ni<double>() << std::endl;
  // std::cout << std::endl;

  vahlen::Matrix<double> E12 = vahlen::E1<double>() * vahlen::E2<double>();
  vahlen::Matrix<double> E21 = vahlen::E2<double>() * vahlen::E1<double>();
  std::cout << E12 << std::endl;
  std::cout << std::endl;
  std::cout << E21 << std::endl;
  std::cout << std::endl;
  std::cout << vahlen::Reverse(E12) << std::endl;
  std::cout << std::endl;

  std::cout << 1.0 * vahlen::E1<double>() + 2.0 * vahlen::E2<double>() +
                   3.0 * vahlen::E3<double>()
            << std::endl;

  return 0;
}
