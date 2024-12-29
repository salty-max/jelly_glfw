#include <jelly/vec.h>

// Vec2 implementation
template <typename T> Vec2<T>::Vec2() : x(0), y(0) {}

template <typename T> Vec2<T>::Vec2(T x, T y) : x(x), y(y) {}

template <typename T> Vec2<T> Vec2<T>::zero() { return Vec2(0, 0); }

template <typename T> Vec2<T> Vec2<T>::one() { return Vec2(1, 1); }

template <typename T> T Vec2<T>::length() const {
  return std::sqrt(x * x + y * y);
}

template <typename T> T Vec2<T>::dot(const Vec2 &other) const {
  return x * other.x + y * other.y;
}

template <typename T> Vec2<T> Vec2<T>::cross(const Vec2 &other) const {
  return Vec2(y * other.x - x * other.y, x * other.y - y * other.x);
}

template <typename T> Vec2<T> Vec2<T>::normalize() const {
  T len = length();
  return Vec2(x / len, y / len);
}

// Operators
template <typename T> Vec2<T> Vec2<T>::operator+(const Vec2 &other) const {
  return Vec2(x + other.x, y + other.y);
}

template <typename T> Vec2<T> Vec2<T>::operator-(const Vec2 &other) const {
  return Vec2(x - other.x, y - other.y);
}

template <typename T> Vec2<T> Vec2<T>::operator*(T scalar) const {
  return Vec2(x * scalar, y * scalar);
}

template <typename T> Vec2<T> Vec2<T>::operator/(T scalar) const {
  return Vec2(x / scalar, y / scalar);
}

template <typename T> Vec2<T> &Vec2<T>::operator+=(const Vec2 &other) {
  x += other.x;
  y += other.y;
  return *this;
}

template <typename T> Vec2<T> &Vec2<T>::operator-=(const Vec2 &other) {
  x -= other.x;
  y -= other.y;
  return *this;
}

template <typename T> Vec2<T> &Vec2<T>::operator*=(T scalar) {
  x *= scalar;
  y *= scalar;
  return *this;
}

template <typename T> Vec2<T> &Vec2<T>::operator/=(T scalar) {
  x /= scalar;
  y /= scalar;
  return *this;
}

template <typename T> T &Vec2<T>::operator[](size_t index) {
  if (index >= 2)
    throw std::out_of_range("Vec2 index out of range");
  return (&x)[index]; // Use pointer arithmetic to access components
}

template <typename T> const T &Vec2<T>::operator[](size_t index) const {
  if (index >= 2)
    throw std::out_of_range("Vec2 index out of range");
  return (&x)[index]; // Use pointer arithmetic to access components
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Vec2<T> &v) {
  os << "(" << v.x << ", " << v.y << ")";
  return os;
}

// Vec3 implementation
template <typename T> Vec3<T>::Vec3() : x(0), y(0), z(0) {}

template <typename T> Vec3<T>::Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

template <typename T> Vec3<T> Vec3<T>::zero() { return Vec3(0, 0, 0); }

template <typename T> Vec3<T> Vec3<T>::one() { return Vec3(1, 1, 1); }

template <typename T> T Vec3<T>::length() const {
  return std::sqrt(x * x + y * y + z * z);
}

template <typename T> T Vec3<T>::dot(const Vec3 &other) const {
  return x * other.x + y * other.y + z * other.z;
}

template <typename T> Vec3<T> Vec3<T>::cross(const Vec3 &other) const {
  return Vec3(y * other.z - z * other.y, z * other.x - x * other.z,
              x * other.y - y * other.x);
}

template <typename T> Vec3<T> Vec3<T>::normalize() const {
  T len = length();
  return Vec3(x / len, y / len, z / len);
}

// Operators
template <typename T> Vec3<T> Vec3<T>::operator+(const Vec3 &other) const {
  return Vec3(x + other.x, y + other.y, z + other.z);
}

template <typename T> Vec3<T> Vec3<T>::operator-(const Vec3 &other) const {
  return Vec3(x - other.x, y - other.y, z - other.z);
}

template <typename T> Vec3<T> Vec3<T>::operator*(T scalar) const {
  return Vec3(x * scalar, y * scalar, z * scalar);
}

template <typename T> Vec3<T> Vec3<T>::operator*(const Vec3 &other) const {
  return Vec3(x * other.x, y * other.y, z * other.z);
}

template <typename T> Vec3<T> Vec3<T>::operator/(T scalar) const {
  return Vec3(x / scalar, y / scalar, z / scalar);
}

template <typename T> Vec3<T> &Vec3<T>::operator+=(const Vec3 &other) {
  x += other.x;
  y += other.y;
  z += other.z;
  return *this;
}

template <typename T> Vec3<T> &Vec3<T>::operator-=(const Vec3 &other) {
  x -= other.x;
  y -= other.y;
  z -= other.z;
  return *this;
}

template <typename T> Vec3<T> &Vec3<T>::operator*=(T scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;
  return *this;
}

template <typename T> Vec3<T> &Vec3<T>::operator*=(const Vec3 &other) {
  x *= other.x;
  y *= other.y;
  z *= other.z;
  return *this;
}

template <typename T> Vec3<T> &Vec3<T>::operator/=(T scalar) {
  x /= scalar;
  y /= scalar;
  z /= scalar;
  return *this;
}

template <typename T> T &Vec3<T>::operator[](size_t index) {
  if (index >= 3)
    throw std::out_of_range("Vec3 index out of range");
  return (&x)[index]; // Use pointer arithmetic to access components
}

template <typename T> const T &Vec3<T>::operator[](size_t index) const {
  if (index >= 3)
    throw std::out_of_range("Vec3 index out of range");
  return (&x)[index]; // Use pointer arithmetic to access components
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Vec3<T> &v) {
  os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return os;
}

// Vec4 implementation
template <typename T> Vec4<T>::Vec4() : x(0), y(0), z(0), w(0) {}

template <typename T>
Vec4<T>::Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

template <typename T> Vec4<T> Vec4<T>::zero() { return Vec4(0, 0, 0, 0); }

template <typename T> Vec4<T> Vec4<T>::one() { return Vec4(1, 1, 1, 1); }

template <typename T> T Vec4<T>::length() const {
  return std::sqrt(x * x + y * y + z * z + w * w);
}

template <typename T> T Vec4<T>::dot(const Vec4 &other) const {
  return x * other.x + y * other.y + z * other.z + w * other.w;
}

template <typename T> Vec4<T> Vec4<T>::cross(const Vec4 &other) const {
  return Vec4(y * other.z - z * other.y, z * other.x - x * other.z,
              x * other.y - y * other.x, 0);
}

template <typename T> Vec4<T> Vec4<T>::normalize() const {
  T len = length();
  return Vec4(x / len, y / len, z / len, w / len);
}

// Operators
template <typename T> Vec4<T> Vec4<T>::operator+(const Vec4 &other) const {
  return Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
}

template <typename T> Vec4<T> Vec4<T>::operator-(const Vec4 &other) const {
  return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
}

template <typename T> Vec4<T> Vec4<T>::operator*(T scalar) const {
  return Vec4(x * scalar, y * scalar, z * scalar, w * scalar);
}

template <typename T> Vec4<T> Vec4<T>::operator/(T scalar) const {
  return Vec4(x / scalar, y / scalar, z / scalar, w / scalar);
}

template <typename T> Vec4<T> &Vec4<T>::operator+=(const Vec4 &other) {
  x += other.x;
  y += other.y;
  z += other.z;
  w += other.w;
  return *this;
}

template <typename T> Vec4<T> &Vec4<T>::operator-=(const Vec4 &other) {
  x -= other.x;
  y -= other.y;
  z -= other.z;
  w -= other.w;
  return *this;
}

template <typename T> Vec4<T> &Vec4<T>::operator*=(T scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;
  w *= scalar;
  return *this;
}

template <typename T> Vec4<T> &Vec4<T>::operator/=(T scalar) {
  x /= scalar;
  y /= scalar;
  z /= scalar;
  w /= scalar;
  return *this;
}

template <typename T> T &Vec4<T>::operator[](size_t index) {
  if (index >= 4)
    throw std::out_of_range("Vec4 index out of range");
  return (&x)[index]; // Use pointer arithmetic to access components
}

template <typename T> const T &Vec4<T>::operator[](size_t index) const {
  if (index >= 4)
    throw std::out_of_range("Vec4 index out of range");
  return (&x)[index]; // Use pointer arithmetic to access components
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Vec4<T> &v) {
  os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
  return os;
}

// Template instantiations
template class Vec2<int>;
template class Vec2<float>;
template class Vec3<int>;
template class Vec3<float>;
template class Vec4<int>;
template class Vec4<float>;
