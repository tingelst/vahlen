#include <Eigen/Core>

namespace vahlen {

  template <typename T>
    using Matrix = Eigen::Matrix<T,8,8>;

  template <typename T>
    Matrix<T> id() {
    return Matrix<T>::Identity();
  }

  template <typename T>
    Matrix<T> e1() {
    Matrix<T> m = Matrix<T>::Zero();
    m(3,0) = T(1.0);
    m(2,1) = T(1.0);
    m(1,2) = T(1.0);
    m(0,3) = T(1.0);
    m(7,4) = T(-1.0);
    m(6,5) = T(-1.0);
    m(5,6) = T(-1.0);
    m(4,7) = T(-1.0);
    return m;
  }

  template <typename T>
    Matrix<T> e2() {
    Matrix<T> m = Matrix<T>::Zero();
    m(2,0) = T(1.0);
    m(3,1) = T(-1.0);
    m(0,2) = T(1.0);
    m(1,3) = T(-1.0);
    m(6,4) = T(-1.0);
    m(7,5) = T(1.0);
    m(4,6) = T(-1.0);
    m(5,7) = T(1.0);
    return m;
  }

  template <typename T>
    Matrix<T> e3() {
    Matrix<T> m = Matrix<T>::Identity();
    m(2,2) = T(-1.0);
    m(3,3) = T(-1.0);
    m(4,4) = T(-1.0);
    m(5,5) = T(-1.0);
    return m;
  }



}
