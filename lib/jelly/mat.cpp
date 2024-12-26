#include <jelly/mat.h>

// Default constructor
template <typename T> Mat4<T>::Mat4() { data = identity().data; }

// Constructor with specific values
template <typename T>
Mat4<T>::Mat4(const std::array<std::array<T, 4>, 4> &values) : data(values) {}

// Constructor with initializer list
template <typename T>
Mat4<T>::Mat4(std::initializer_list<std::initializer_list<T>> values) {
  size_t row = 0;
  for (auto &r : values) {
    size_t col = 0;
    for (auto &c : r) {
      data[row][col] = c;
      ++col;
    }
    ++row;
  }
}

// Identity matrix
template <typename T> Mat4<T> Mat4<T>::identity() {
  return Mat4<T>({
      {T(1), T(0), T(0), T(0)},
      {T(0), T(1), T(0), T(0)},
      {T(0), T(0), T(1), T(0)},
      {T(0), T(0), T(0), T(1)},
  });
}

// Translation matrix
template <typename T> Mat4<T> Mat4<T>::translate(const Vec3<T> &translation) {
  return Mat4<T>({
      {T(1), T(0), T(0), translation.x},
      {T(0), T(1), T(0), translation.y},
      {T(0), T(0), T(1), translation.z},
      {T(0), T(0), T(0), T(1)},
  });
}

// Scaling matrix
template <typename T> Mat4<T> Mat4<T>::scale(const Vec3<T> &scale) {
  return Mat4<T>({
      {scale.x, T(0), T(0), T(0)},
      {T(0), scale.y, T(0), T(0)},
      {T(0), T(0), scale.z, T(0)},
      {T(0), T(0), T(0), T(1)},
  });
}

// Anisotropic scaling matrix
template <typename T> Mat4<T> Mat4<T>::scale_aniso(const Vec3<T> &scale) {
  return Mat4<T>::scale(scale);
}

// Rotation matrix (Z-axis)
template <typename T> Mat4<T> Mat4<T>::rotateZ(T angle) {
  T c = std::cos(angle);
  T s = std::sin(angle);
  return Mat4<T>({
      {c, -s, T(0), T(0)},
      {s, c, T(0), T(0)},
      {T(0), T(0), T(1), T(0)},
      {T(0), T(0), T(0), T(1)},
  });
}

// Orthographic projection matrix
template <typename T>
Mat4<T> Mat4<T>::ortho(T left, T right, T bottom, T top, T near, T far) {
  return Mat4<T>({
      {T(2) / (right - left), T(0), T(0), -(right + left) / (right - left)},
      {T(0), T(2) / (top - bottom), T(0), -(top + bottom) / (top - bottom)},
      {T(0), T(0), -T(2) / (far - near), -(far + near) / (far - near)},
      {T(0), T(0), T(0), T(1)},
  });
}

// Perspective projection matrix
template <typename T>
Mat4<T> Mat4<T>::projection(T fov, T aspect, T near, T far) {
  T tanHalfFov = std::tan(fov / T(2));
  return Mat4<T>({
      {T(1) / (aspect * tanHalfFov), T(0), T(0), T(0)},
      {T(0), T(1) / tanHalfFov, T(0), T(0)},
      {T(0), T(0), -(far + near) / (far - near),
       -T(2) * far * near / (far - near)},
      {T(0), T(0), -T(1), T(0)},
  });
}

// Look-at matrix
template <typename T>
Mat4<T> Mat4<T>::look_at(const Vec3<T> &eye, const Vec3<T> &center,
                         const Vec3<T> &up) {
  Vec3<T> f = (center - eye).normalize();
  Vec3<T> s = f.cross(up.normalize());
  Vec3<T> u = s.cross(f);

  return Mat4<T>({
      {s.x, s.y, s.z, -eye.dot(s)},
      {u.x, u.y, u.z, -eye.dot(u)},
      {-f.x, -f.y, -f.z, eye.dot(f)},
      {T(0), T(0), T(0), T(1)},
  });
}

// Matrix multiplication
template <typename T> Mat4<T> Mat4<T>::multiply(const Mat4 &other) const {
  Mat4<T> result;
  for (size_t i = 0; i < 4; ++i) {
    for (size_t j = 0; j < 4; ++j) {
      result.data[i][j] = T(0);
      for (size_t k = 0; k < 4; ++k) {
        result.data[i][j] += data[i][k] * other.data[k][j];
      }
    }
  }
  return result;
}

// Transpose the matrix
template <typename T> Mat4<T> Mat4<T>::transpose() const {
  Mat4<T> result;
  for (size_t i = 0; i < 4; ++i) {
    for (size_t j = 0; j < 4; ++j) {
      result.data[i][j] = data[j][i];
    }
  }
  return result;
}

// Access element (non-const)
template <typename T> T &Mat4<T>::at(size_t row, size_t col) {
  return data[row][col];
}

// Access element (const)
template <typename T> const T &Mat4<T>::at(size_t row, size_t col) const {
  return data[row][col];
}

// Explicit template instantiation
template class Mat4<float>;
template class Mat4<int>;
