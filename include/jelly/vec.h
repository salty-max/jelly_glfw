#ifndef VEC_H
#define VEC_H

#include <cmath>
#include <stdexcept>

/**
 * @brief A 2D vector class.
 *
 * @tparam T The data type of the vector elements.
 */
template <typename T = float> class Vec2 {
public:
  T x, y;

  /**
   * @brief Default constructor.
   */
  Vec2();

  /**
   * @brief Constructor with x and y values.
   * @param x The x value.
   * @param y The y value.
   */
  Vec2(T x, T y);

  /**
   * @brief Returns a zero vector.
   * @return A zero vector.
   */
  static Vec2 zero();

  /**
   * @brief Returns a one vector.
   * @return A one vector.
   */
  static Vec2 one();

  /**
   * @brief Returns the length of the vector.
   * @return The length of the vector.
   */
  T length() const;

  /**
   * @brief Returns the dot product of this vector and another vector.
   * @param other The other vector.
   * @return The dot product.
   */
  T dot(const Vec2 &other) const;

  /**
   * @brief Returns the cross product of this vector and another vector.
   * @param other The other vector.
   * @return The cross product.
   */
  Vec2 cross(const Vec2 &other) const;

  /**
   * @brief Returns the normalized version of this vector.
   * @return The normalized vector.
   */
  Vec2 normalize() const;

  Vec2 operator+(const Vec2 &other) const;
  Vec2 operator-(const Vec2 &other) const;
  Vec2 operator*(T scalar) const;
  Vec2 operator/(T scalar) const;

  Vec2 &operator+=(const Vec2 &other);
  Vec2 &operator-=(const Vec2 &other);
  Vec2 &operator*=(T scalar);
  Vec2 &operator/=(T scalar);

  T &operator[](size_t index);
  const T &operator[](size_t index) const;
};

/**
 * @brief A 3D vector class.
 */
template <typename T = float> class Vec3 {
public:
  T x, y, z;

  /**
   * @brief Default constructor.
   */
  Vec3();

  /**
   * @brief Constructor with x, y, and z values.
   * @param x The x value.
   * @param y The y value.
   * @param z The z value.
   */
  Vec3(T x, T y, T z);

  /**
   * @brief Returns a zero vector.
   * @return A zero vector.
   */
  static Vec3 zero();

  /**
   * @brief Returns a one vector.
   * @return A one vector.
   */
  static Vec3 one();

  /**
   * @brief Returns the length of the vector.
   * @return The length of the vector.
   */
  T length() const;

  /**
   * @brief Returns the dot product of this vector and another vector.
   * @param other The other vector.
   * @return The dot product.
   */
  T dot(const Vec3 &other) const;

  /**
   * @brief Returns the cross product of this vector and another vector.
   * @param other The other vector.
   * @return The cross product.
   */
  Vec3 cross(const Vec3 &other) const;

  /**
   * @brief Returns the normalized version of this vector.
   * @return The normalized vector.
   */
  Vec3 normalize() const;

  Vec3 operator+(const Vec3 &other) const;
  Vec3 operator-(const Vec3 &other) const;
  Vec3 operator*(T scalar) const;
  Vec3 operator*(const Vec3 &other) const;
  Vec3 operator/(T scalar) const;

  Vec3 &operator+=(const Vec3 &other);
  Vec3 &operator-=(const Vec3 &other);
  Vec3 &operator*=(T scalar);
  Vec3 &operator*=(const Vec3 &other);
  Vec3 &operator/=(T scalar);

  T &operator[](size_t index);
  const T &operator[](size_t index) const;
};

/**
 * @brief A 4D vector class.
 *
 * @tparam T The data type of the vector elements.
 */
template <typename T = float> class Vec4 {
public:
  T x, y, z, w;

  /**
   * @brief Default constructor.
   */
  Vec4();

  /**
   * @brief Constructor with x, y, z, and w values.
   * @param x The x value.
   * @param y The y value.
   * @param z The z value.
   * @param w The w value.
   */
  Vec4(T x, T y, T z, T w);

  /**
   * @brief Returns a zero vector.
   * @return A zero vector.
   */
  static Vec4 zero();

  /**
   * @brief Returns a one vector.
   * @return A one vector.
   */
  static Vec4 one();

  /**
   * @brief Returns the length of the vector.
   * @return The length of the vector.
   */
  T length() const;

  /**
   * @brief Returns the dot product of this vector and another vector.
   * @param other The other vector.
   * @return The dot product.
   */
  T dot(const Vec4 &other) const;

  /**
   * @brief Returns the cross product of this vector and another vector.
   * @param other The other vector.
   * @return The cross product.
   */
  Vec4 cross(const Vec4 &other) const;

  /**
   * @brief Returns the normalized version of this vector.
   * @return The normalized vector.
   */
  Vec4 normalize() const;

  Vec4 operator+(const Vec4 &other) const;
  Vec4 operator-(const Vec4 &other) const;
  Vec4 operator*(T scalar) const;
  Vec4 operator/(T scalar) const;

  Vec4 &operator+=(const Vec4 &other);
  Vec4 &operator-=(const Vec4 &other);
  Vec4 &operator*=(T scalar);
  Vec4 &operator/=(T scalar);

  T &operator[](size_t index);
  const T &operator[](size_t index) const;
};

#endif // VEC_H
