#include "jelly/mat.h"

template <typename T> Mat4<T>::Mat4() {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      data_[i][j] = (i == j) ? static_cast<T>(1) : static_cast<T>(0);
    }
  }
}

template <typename T>
Mat4<T>::Mat4(const std::array<std::array<T, 4>, 4> &values) : data_(values) {}

template <typename T> Mat4<T>::Mat4(std::initializer_list<T> values) {
  if (values.size() != 16) {
    throw std::invalid_argument(
        "Mat4 constructor requires exactly 16 elements.");
  }
  size_t i = 0;
  for (auto it = values.begin(); it != values.end(); ++it) {
    data_[i / 4][i % 4] = *it; // Fill in column-major order
    ++i;
  }
}

template <typename T> Mat4<T> Mat4<T>::identity() {
  Mat4 result;
  return result;
}

template <typename T> Mat4<T> Mat4<T>::translate(const Vec3<T> &translation) {
  Mat4 mat = identity();
  mat.data_[0][3] = translation.x;
  mat.data_[1][3] = translation.y;
  mat.data_[2][3] = translation.z;
  return mat;
}

template <typename T> Mat4<T> Mat4<T>::scale(const Vec3<T> &scale) {
  Mat4 mat = identity();
  mat.data_[0][0] = scale.x;
  mat.data_[1][1] = scale.y;
  mat.data_[2][2] = scale.z;
  return mat;
}

template <typename T> Mat4<T> Mat4<T>::rotateX(T angle) {
  Mat4 mat = identity();
  T c = std::cos(angle), s = std::sin(angle);
  mat.data_[1][1] = c;
  mat.data_[1][2] = -s;
  mat.data_[2][1] = s;
  mat.data_[2][2] = c;
  return mat;
}

template <typename T> Mat4<T> Mat4<T>::rotateY(T angle) {
  Mat4 mat = identity();
  T c = std::cos(angle), s = std::sin(angle);
  mat.data_[0][0] = c;
  mat.data_[0][2] = s;
  mat.data_[2][0] = -s;
  mat.data_[2][2] = c;
  return mat;
}

template <typename T> Mat4<T> Mat4<T>::rotateZ(T angle) {
  Mat4 mat = identity();
  T c = std::cos(angle), s = std::sin(angle);
  mat.data_[0][0] = c;
  mat.data_[0][1] = -s;
  mat.data_[1][0] = s;
  mat.data_[1][1] = c;
  return mat;
}

template <typename T> Mat4<T> Mat4<T>::rotate(const Vec3<T> &axis, T angle) {
  Mat4 mat = identity();
  T c = std::cos(angle), s = std::sin(angle), t = 1 - c;
  T x = axis.x, y = axis.y, z = axis.z;

  mat.data_[0][0] = t * x * x + c;
  mat.data_[0][1] = t * x * y - s * z;
  mat.data_[0][2] = t * x * z + s * y;
  mat.data_[1][0] = t * x * y + s * z;
  mat.data_[1][1] = t * y * y + c;
  mat.data_[1][2] = t * y * z - s * x;
  mat.data_[2][0] = t * x * z - s * y;
  mat.data_[2][1] = t * y * z + s * x;
  mat.data_[2][2] = t * z * z + c;

  return mat;
}

template <typename T>
Mat4<T> Mat4<T>::ortho(T left, T right, T bottom, T top, T near, T far) {
  Mat4 mat = identity();
  mat.data_[0][0] = static_cast<T>(2) / (right - left);
  mat.data_[1][1] = static_cast<T>(2) / (top - bottom);
  mat.data_[2][2] = static_cast<T>(-2) / (far - near);
  mat.data_[3][0] = -(right + left) / (right - left);
  mat.data_[3][1] = -(top + bottom) / (top - bottom);
  mat.data_[3][2] = -(far + near) / (far - near);
  return mat;
}

template <typename T>
Mat4<T> Mat4<T>::perspective(T fov, T aspect, T near, T far) {
  Mat4 mat = {};
  T tanHalfFov = std::tan(fov / static_cast<T>(2));

  mat.data_[0][0] = static_cast<T>(1) / (aspect * tanHalfFov);
  mat.data_[1][1] = static_cast<T>(1) / tanHalfFov;
  mat.data_[2][2] = -(far + near) / (far - near);
  mat.data_[2][3] = -(static_cast<T>(2) * far * near) / (far - near);
  mat.data_[3][2] = static_cast<T>(-1);
  return mat;
}

template <typename T>
Mat4<T> Mat4<T>::look_at(const Vec3<T> &eye, const Vec3<T> center,
                         const Vec3<T> &up) {
  Vec3<T> f = (center - eye).normalize();
  Vec3<T> s = f.cross(up.normalize()).normalize();
  Vec3<T> u = s.cross(f);

  Mat4 mat = identity();
  mat.data_[0][0] = s.x;
  mat.data_[0][1] = s.y;
  mat.data_[0][2] = s.z;
  mat.data_[0][3] = -s.dot(eye);
  mat.data_[1][0] = u.x;
  mat.data_[1][1] = u.y;
  mat.data_[1][2] = u.z;
  mat.data_[1][3] = -u.dot(eye);
  mat.data_[2][0] = -f.x;
  mat.data_[2][1] = -f.y;
  mat.data_[2][2] = -f.z;
  mat.data_[2][3] = f.dot(eye);
  return mat;
}

template <typename T> Mat4<T> Mat4<T>::multiply(const Mat4 &other) const {
  Mat4 result;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      result.data_[i][j] = static_cast<T>(0);
      for (int k = 0; k < 4; ++k) {
        result.data_[i][j] += data_[i][k] * other.data_[k][j];
      }
    }
  }
  return result;
}

template <typename T> Mat4<T> Mat4<T>::transpose() const {
  Mat4 result;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      result.data_[i][j] = data_[j][i];
    }
  }
  return result;
}

template <typename T> T &Mat4<T>::at(size_t row, size_t col) {
  if (row >= 4 || col >= 4)
    throw std::out_of_range("Matrix index out of bounds");
  return data_[row][col];
}

template <typename T> const T &Mat4<T>::at(size_t row, size_t col) const {
  if (row >= 4 || col >= 4)
    throw std::out_of_range("Matrix index out of bounds");
  return data_[row][col];
}

template <typename T> const T *Mat4<T>::value_ptr() const {
  return &data_[0][0];
}

template <typename T> void Mat4<T>::print() const {
  for (const auto &row : data_) {
    for (const auto &val : row) {
      std::cout << std::setw(10) << val << " ";
    }
    std::cout << std::endl;
  }
}

template <typename T> Mat4<T> Mat4<T>::operator*(const Mat4 &other) const {
  return multiply(other);
}

template <typename T> Vec3<T> Mat4<T>::operator*(const Vec3<T> &vec) const {
  Vec3<T> result;
  result.x = data_[0][0] * vec.x + data_[0][1] * vec.y + data_[0][2] * vec.z +
             data_[0][3];
  result.y = data_[1][0] * vec.x + data_[1][1] * vec.y + data_[1][2] * vec.z +
             data_[1][3];
  result.z = data_[2][0] * vec.x + data_[2][1] * vec.y + data_[2][2] * vec.z +
             data_[2][3];
  T w = data_[3][0] * vec.x + data_[3][1] * vec.y + data_[3][2] * vec.z +
        data_[3][3];
  return Vec3<T>(result.x / w, result.y / w, result.z / w);
}

template <typename T> Vec4<T> Mat4<T>::operator*(const Vec4<T> &vec) const {
  Vec4<T> result;
  for (int i = 0; i < 4; ++i) {
    result[i] = data_[i][0] * vec.x + data_[i][1] * vec.y +
                data_[i][2] * vec.z + data_[i][3] * vec.w;
  }
  return result;
}

template <typename T> Mat4<T> &Mat4<T>::operator*=(const Mat4 &other) {
  *this = multiply(other);
  return *this;
}

template <typename T> Mat4<T> Mat4<T>::operator+(const Mat4 &other) const {
  Mat4 result;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      result.data_[i][j] = data_[i][j] + other.data_[i][j];
    }
  }
  return result;
}

template <typename T> Mat4<T> &Mat4<T>::operator+=(const Mat4 &other) {
  *this = *this + other;
  return *this;
}

template <typename T> bool Mat4<T>::operator==(const Mat4 &other) const {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (data_[i][j] != other.data_[i][j])
        return false;
    }
  }
  return true;
}

// Explicit instantiations
template class Mat4<int>;
template class Mat4<float>;