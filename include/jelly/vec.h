#ifndef VEC_H
#define VEC_H

#include <cmath>

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
  Vec3 operator/(T scalar) const;

  Vec3 &operator+=(const Vec3 &other);
  Vec3 &operator-=(const Vec3 &other);
  Vec3 &operator*=(T scalar);
  Vec3 &operator/=(T scalar);
};

#endif // VEC_H
