#pragma once

#include <Eigen/Core>

namespace vahlen {

template <typename T> using Matrix = Eigen::Matrix<T, 8, 8>;

template <typename T> using Matrix44 = Eigen::Matrix<T, 4, 4>;

template <typename T> using Matrix22 = Eigen::Matrix<T, 2, 2>;

template <typename T> Matrix<T> Mnk() {
  Matrix<T> m = Matrix<T>::Identity();
  m(4, 4) = T(-1.0);
  m(5, 5) = T(-1.0);
  m(6, 6) = T(-1.0);
  m(7, 7) = T(-1.0);
  return m;
}

template <typename T> Matrix<T> Id() { return Matrix<T>::Identity(); }

template <typename T> Matrix<T> E1() {
  Matrix<T> m = Matrix<T>::Zero();
  m(2, 0) = T(1.0);
  m(3, 1) = T(1.0);
  m(0, 2) = T(1.0);
  m(1, 3) = T(1.0);
  m(6, 4) = T(-1.0);
  m(7, 5) = T(-1.0);
  m(4, 6) = T(-1.0);
  m(5, 7) = T(-1.0);
  return m;
}

template <typename T> Matrix<T> E2() {
  Matrix<T> m = Matrix<T>::Zero();
  m(3, 0) = T(1.0);
  m(2, 1) = T(-1.0);
  m(1, 2) = T(-1.0);
  m(0, 3) = T(1.0);
  m(7, 4) = T(-1.0);
  m(6, 5) = T(1.0);
  m(5, 6) = T(1.0);
  m(4, 7) = T(-1.0);
  return m;
}

template <typename T> Matrix<T> E3() {
  Matrix<T> m = Matrix<T>::Identity();
  m(2, 2) = T(-1.0);
  m(3, 3) = T(-1.0);
  m(4, 4) = T(-1.0);
  m(5, 5) = T(-1.0);
  return m;
}

template <typename T> Matrix<T> E12() { return E1<T>() * E2<T>(); }

template <typename T> Matrix<T> E13() { return E1<T>() * E3<T>(); }

template <typename T> Matrix<T> E23() { return E2<T>() * E3<T>(); }

template <typename T> Matrix<T> E123() { return E1<T>() * E2<T>() * E3<T>(); }

template <typename T> Matrix<T> Ni() {
  Matrix<T> m = Matrix<T>::Zero();
  m(0, 4) = T(-2.0);
  m(1, 5) = T(-2.0);
  m(2, 6) = T(-2.0);
  m(3, 7) = T(-2.0);
  return m;
}

template <typename T> Matrix<T> No() {
  Matrix<T> m = Matrix<T>::Zero();
  m(4, 0) = T(1.0);
  m(5, 1) = T(1.0);
  m(6, 2) = T(1.0);
  m(7, 3) = T(1.0);
  return m;
}

template <typename T> Matrix22<T> ComplexConjugate(const Matrix22<T> x) {
  T a = x(0, 0);
  T b = x(0, 1);
  T c = x(1, 0);
  T d = x(1, 1);
  Matrix22<T> m;
  m << a, -b, -c, d;
  return m;
}
template <typename T> Matrix44<T> Reverse(const Matrix44<T> x) {
  Matrix22<T> a = x.topLeftCorner(2, 2);
  Matrix22<T> b = x.topRightCorner(2, 2);
  Matrix22<T> c = x.bottomLeftCorner(2, 2);
  Matrix22<T> d = x.bottomRightCorner(2, 2);
  Matrix44<T> m;
  m.topLeftCorner(2, 2) = ComplexConjugate(a);
  m.topRightCorner(2, 2) = ComplexConjugate(c);
  m.bottomLeftCorner(2, 2) = ComplexConjugate(b);
  m.bottomRightCorner(2, 2) = ComplexConjugate(d);
  return m;
}

template <typename T> Matrix44<T> CliffordConjugate(const Matrix44<T> x) {
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

template <typename T> Matrix<T> Inverse(const Matrix<T> &x) {
  Matrix44<T> a = x.topLeftCorner(4, 4);
  Matrix44<T> b = x.topRightCorner(4, 4);
  Matrix44<T> c = x.bottomLeftCorner(4, 4);
  Matrix44<T> d = x.bottomRightCorner(4, 4);

  Matrix44<T> det_matrix = a * Reverse(d) - b * Reverse(c);
  T det = det_matrix(0, 0);

  Matrix<T> m;
  m.topLeftCorner(4, 4) = Reverse(d);
  m.topRightCorner(4, 4) = -Reverse(b);
  m.bottomLeftCorner(4, 4) = -Reverse(c);
  m.bottomRightCorner(4, 4) = Reverse(a);
  return m / det;
}
template <typename T> Matrix<T> Reverse(const Matrix<T> &x) {
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

template <typename T>
Matrix<T> InnerProduct(const Matrix<T> &a, const Matrix<T> &b) {
  return T(0.5) * (a * b - b * a);
}

template <typename T>
Matrix<T> OuterProduct(const Matrix<T> &a, const Matrix<T> &b) {
  return T(0.5) * (a * b + b * a);
}

template <typename T>
Matrix<T> ProjectVectorBivector(const Matrix<T> &a, const Matrix<T> &b) {
  return InnerProduct(a, b) * Inverse(b);
}

template <typename T>
Matrix<T> RejectVectorBivector(const Matrix<T> &a, const Matrix<T> &b) {
  return OuterProduct(a, b) * Inverse(b);
}

template <typename T> Matrix<T> Point(const Matrix<T> &x) {
  return x + T(0.5) * x * x * Ni<T>() + No<T>();
}

template <typename T> Matrix<T> Point(const T x, const T y, const T z) {
  Matrix<T> m = x * E1<T>() + y * E2<T>() + z * E3<T>();
  return Point<T>(m);
}

template <typename T> Matrix<T> Point(const T *x) {
  Matrix<T> m = x[0] * E1<T>() + x[1] * E2<T>() + x[2] * E3<T>();
  return Point<T>(m);
}

template <typename T> Matrix<T> Rotor(const T *x) {
  return x[0] * Id<T>() + x[1] * E12<T>() + x[2] * E13<T>() + x[3] * E23<T>();
}

template <typename T> Matrix<T> Translator(const T *x) {
  return x[0] * Id<T>() + x[1] * E1<T>() * Ni<T>() + x[2] * E2<T>() * Ni<T>() +
         x[3] * E3<T>() * Ni<T>();
}

template <typename T> Matrix<T> Motor(const T *x) {
  return x[0] * Id<T>() + x[1] * E12<T>() + x[2] * E13<T>() + x[3] * E23<T>() +
         x[4] * E1<T>() * Ni<T>() + x[5] * E2<T>() * Ni<T>() +
         x[6] * E3<T>() * Ni<T>() + x[7] * E123<T>() * Ni<T>();
}

} // namespace vahlen
