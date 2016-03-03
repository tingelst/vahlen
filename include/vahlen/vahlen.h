#include <Eigen/Core>

namespace vahlen {

template <typename T>
using Matrix = Eigen::Matrix<T, 8, 8>;

template <typename T>
using Matrix44 = Eigen::Matrix<T, 4, 4>;

template <typename T>
using Matrix22 = Eigen::Matrix<T, 2, 2>;

template <typename T>
Matrix<T> Id() {
  return Matrix<T>::Identity();
}

template <typename T>
Matrix<T> E1() {
  Matrix<T> m = Matrix<T>::Zero();
  m(3, 0) = T(1.0);
  m(2, 1) = T(1.0);
  m(1, 2) = T(1.0);
  m(0, 3) = T(1.0);
  m(7, 4) = T(-1.0);
  m(6, 5) = T(-1.0);
  m(5, 6) = T(-1.0);
  m(4, 7) = T(-1.0);
  return m;
}

template <typename T>
Matrix<T> E2() {
  Matrix<T> m = Matrix<T>::Zero();
  m(2, 0) = T(1.0);
  m(3, 1) = T(-1.0);
  m(0, 2) = T(1.0);
  m(1, 3) = T(-1.0);
  m(6, 4) = T(-1.0);
  m(7, 5) = T(1.0);
  m(4, 6) = T(-1.0);
  m(5, 7) = T(1.0);
  return m;
}

template <typename T>
Matrix<T> E3() {
  Matrix<T> m = Matrix<T>::Identity();
  m(2, 2) = T(-1.0);
  m(3, 3) = T(-1.0);
  m(4, 4) = T(-1.0);
  m(5, 5) = T(-1.0);
  return m;
}

template <typename T>
Matrix<T> Ni() {
  Matrix<T> m = Matrix<T>::Zero();
  m(0, 4) = T(-2.0);
  m(1, 5) = T(-2.0);
  m(2, 6) = T(-2.0);
  m(3, 7) = T(-2.0);
  return m;
}

template <typename T>
Matrix<T> No() {
  Matrix<T> m = Matrix<T>::Zero();
  m(4, 0) = T(1.0);
  m(5, 1) = T(1.0);
  m(6, 2) = T(1.0);
  m(7, 3) = T(1.0);
  return m;
}

template <typename T>
Matrix44<T> CliffordConjugate(const Matrix44<T> x) {
  Matrix22<T> a = x.topLeftCorner(2, 2);
  Matrix22<T> b = x.topRightCorner(2, 2);
  Matrix22<T> c = x.bottomLeftCorner(2, 2);
  Matrix22<T> d = x.bottomRightCorner(2, 2);
  Matrix44<T> m;
  m.topLeftCorner(2, 2) = d;
  m.topRightCorner(2, 2) = T(-1.0) * b;
  m.bottomLeftCorner(2, 2) = T(-1.0) * c;
  m.bottomRightCorner(2, 2) = a;
  return m;
}

template <typename T>
Matrix<T> Reverse(const Matrix<T>& x) {
  // a + ib = [[a -b]
  //           [b  a]]

  Matrix44<T> a = x.topLeftCorner(4, 4);
  Matrix44<T> b = x.topRightCorner(4, 4);
  Matrix44<T> c = x.bottomLeftCorner(4, 4);
  Matrix44<T> d = x.bottomRightCorner(4, 4);

  Matrix<T> m;
  m.topLeftCorner(4, 4) = CliffordConjugate(d);
  m.topRightCorner(4, 4) = CliffordConjugate(b);
  m.bottomLeftCorner(4, 4) = CliffordConjugate(c);
  m.bottomRightCorner(4, 4) = CliffordConjugate(a);
  return m;
}
}
