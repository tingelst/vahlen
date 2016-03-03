#include <iostream>
#include <Eigen/Core>

#include <vahlen/vahlen.h>

int main() {
  // std::cout << vahlen::id<double>() << std::endl;

  std::cout << vahlen::e1<double>() << std::endl;
  std::cout << std::endl;
  std::cout << vahlen::e2<double>() << std::endl;
  std::cout << std::endl;
  std::cout << vahlen::e3<double>() << std::endl;
  std::cout << std::endl;

  return 0;
}
