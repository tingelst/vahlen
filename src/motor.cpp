#include <iostream>

#include <vahlen/vahlen.h>

const double kPi = 3.141592653589793238462643383279;

using Mat = vahlen::Matrix<double>;

int main() {
  // std::cout << vahlen::id<double>() << std::endl;

  Mat e1 = vahlen::E1<double>() * vahlen::Mnk<double>();
  Mat e2 = vahlen::E2<double>() * vahlen::Mnk<double>();
  Mat e3 = vahlen::E3<double>() * vahlen::Mnk<double>();
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
  Mat e12 = 0.5 * (e1 * e2 - e2 * e1);
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
  std::cout << std::endl;

  Mat motor = translator * rotor;
  std::cout << motor << std::endl;

  vahlen::Matrix44<double> A =
      (motor * vahlen::Mnk<double>()).topLeftCorner(4, 4);
  std::cout << A << std::endl;
  std::cout << std::endl;

  std::cout << vahlen::InnerProduct<double>(e1, e12) << std::endl;
  std::cout << std::endl;
  std::cout << e2 << std::endl;
  std::cout << std::endl;

  vahlen::Matrix22<double> complex;
  complex << 1.0, -2.0, 2.0, 1.0;
  std::cout << complex << std::endl;
  std::cout << std::endl;
  std::cout << vahlen::ComplexConjugate(complex) << std::endl;
  std::cout << std::endl;

  Mat biv = vahlen::E12<double>() + 2. * vahlen::E13<double>() +
            3. * vahlen::E23<double>();
  std::cout << vahlen::Inverse(biv) << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << vahlen::E1<double>() << std::endl;
  std::cout << std::endl;
  std::cout << vahlen::E2<double>() << std::endl;
  std::cout << std::endl;
  std::cout << vahlen::E3<double>() << std::endl;
  std::cout << std::endl;


  double m_arr[8] = {1., 2., 3., 4., 5., 6., 7., 8.};
  Mat mot = vahlen::Motor<double>(m_arr);
  vahlen::Matrix44<double> rot = mot.topLeftCorner(4,4);
  vahlen::Matrix44<double> trans = mot.topRightCorner(4,4);
  
  std::cout << trans * vahlen::Reverse(rot) << std::endl;
  std::cout << std::endl;

  return 0;
}
