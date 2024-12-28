#ifndef MAT_H
#define MAT_H

#include <array>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <initializer_list>

#include <jelly/vec.h>

/**
 * @brief A 4x4 matrix class for linear algebra operations.
 *
 * @tparam T Type of the matrix elements (default: float).
 */
template <typename T = float> class Mat4 {
  std::array<std::array<T, 4>, 4>
      data_; /**< Internal data storage for the matrix. */

public:
  /**
   * @brief Default constructor: Initializes the matrix as an identity matrix.
   */
  Mat4();

  /**
   * @brief Constructor that initializes the matrix with specific values.
   *
   * @param values A 2D array of values to initialize the matrix.
   */
  Mat4(const std::array<std::array<T, 4>, 4> &values);

  /**
   * @brief Constructor that initializes the matrix using an initializer list.
   *
   * @param values A nested initializer list to initialize the matrix.
   */
  Mat4(std::initializer_list<T> values);

  /**
   * @brief Creates an identity matrix.
   *
   * @return An identity matrix.
   */
  static Mat4 identity();

  /**
   * @brief Creates a translation matrix.
   *
   * @param translation A vector representing the translation in x, y, z axes.
   * @return A translation matrix.
   */
  static Mat4 translate(const Vec3<T> &translation);

  /**
   * @brief Creates a scaling matrix.
   *
   * @param scale A vector representing scaling factors for x, y, z axes.
   * @return A scaling matrix.
   */
  static Mat4 scale(const Vec3<T> &scale);

  /**
   * @brief Creates a matrix for rotation around the X axis.
   *
   * @param angle Rotation angle in radians.
   * @return A rotation matrix around the X axis.
   */
  static Mat4 rotateX(T angle);

  /**
   * @brief Creates a matrix for rotation around the Y axis.
   *
   * @param angle Rotation angle in radians.
   * @return A rotation matrix around the Y axis.
   */
  static Mat4 rotateY(T angle);

  /**
   * @brief Creates a matrix for rotation around the Z axis.
   *
   * @param angle Rotation angle in radians.
   * @return A rotation matrix around the Z axis.
   */
  static Mat4 rotateZ(T angle);

  /**
   * @brief Creates a matrix for rotation around an arbitrary axis.
   *
   * @param axis A vector representing the axis of rotation.
   * @param angle Rotation angle in radians.
   * @return A rotation matrix around the specified axis.
   */
  static Mat4 rotate(const Vec3<T> &axis, T angle);

  /**
   * @brief Creates an orthographic projection matrix.
   *
   * @param left Left clipping plane.
   * @param right Right clipping plane.
   * @param bottom Bottom clipping plane.
   * @param top Top clipping plane.
   * @param near Near clipping plane.
   * @param far Far clipping plane.
   * @return An orthographic projection matrix.
   */
  static Mat4 ortho(T left, T right, T bottom, T top, T near, T far);

  /**
   * @brief Creates a perspective projection matrix.
   *
   * @param fov Field of view angle in radians.
   * @param aspect Aspect ratio of the view.
   * @param near Near clipping plane.
   * @param far Far clipping plane.
   * @return A perspective projection matrix.
   */
  static Mat4 perspective(T fov, T aspect, T near, T far);

  /**
   * @brief Creates a view matrix using the look-at method.
   *
   * @param eye Position of the camera.
   * @param center Target position the camera is looking at.
   * @param up Up vector for the camera.
   * @return A view matrix.
   */
  static Mat4 look_at(const Vec3<T> &eye, const Vec3<T> center,
                      const Vec3<T> &up);

  /**
   * @brief Multiplies the current matrix with another matrix.
   *
   * @param other The other matrix to multiply.
   * @return The result of the multiplication.
   */
  Mat4 multiply(const Mat4 &other) const;

  /**
   * @brief Computes the transpose of the matrix.
   *
   * @return The transposed matrix.
   */
  Mat4 transpose() const;

  /**
   * @brief Accesses a specific element of the matrix.
   *
   * @param row Row index (0-3).
   * @param col Column index (0-3).
   * @return A reference to the element at the specified row and column.
   */
  T &at(size_t row, size_t col);

  /**
   * @brief Accesses a specific element of the matrix (const version).
   *
   * @param row Row index (0-3).
   * @param col Column index (0-3).
   * @return A const reference to the element at the specified row and column.
   */
  const T &at(size_t row, size_t col) const;

  /**
   * @brief Provides a pointer to the matrix data.
   *
   * @return A pointer to the matrix's internal data array.
   */
  const T *value_ptr() const;

  // Operator overloads

  /**
   * @brief Matrix multiplication operator.
   *
   * @param other The other matrix to multiply with.
   * @return The result of the multiplication.
   */
  Mat4 operator*(const Mat4 &other) const;

  /**
   * @brief Multiplies the matrix with a 3D vector.
   *
   * @param vec The vector to multiply with.
   * @return The resulting transformed vector.
   */
  Vec3<T> operator*(const Vec3<T> &vec) const;

  /**
   * @brief Multiplies the matrix with a 4D vector.
   *
   * @param vec The vector to multiply with.
   * @return The resulting transformed vector.
   */
  Vec4<T> operator*(const Vec4<T> &vec) const;

  /**
   * @brief Matrix multiplication and assignment operator.
   *
   * @param other The other matrix to multiply with.
   * @return A reference to the modified matrix.
   */
  Mat4 &operator*=(const Mat4 &other);

  /**
   * @brief Matrix addition operator.
   *
   * @param other The other matrix to add.
   * @return The result of the addition.
   */
  Mat4 operator+(const Mat4 &other) const;

  /**
   * @brief Matrix addition and assignment operator.
   *
   * @param other The other matrix to add.
   * @return A reference to the modified matrix.
   */
  Mat4 &operator+=(const Mat4 &other);

  /**
   * @brief Equality comparison operator.
   *
   * @param other The other matrix to compare.
   * @return True if the matrices are equal, false otherwise.
   */
  bool operator==(const Mat4 &other) const;

  /**
   * @brief Prints the matrix to the console (for debugging).
   */
  void print() const;
};

#endif // MAT_H