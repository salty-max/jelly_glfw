#ifndef MAT_H
#define MAT_H

#include <array>
#include <cstddef>
#include <cmath>

#include <jelly/vec.h>

/**
 * @brief A 4x4 Matrix class.
 */
template <typename T = float> class Mat4 {
public:
  std::array<std::array<T, 4>, 4> data;

  /**
   * @brief Default constructor.
   * Constructs an identity matrix.
   */
  Mat4();

  /**
   * @brief Constructor with specific values.
   * @param values 2D array containing matrix values.
   */
  Mat4(const std::array<std::array<T, 4>, 4> &values);

  /**
   * @brief Constructor with initializer list.
   * @param values Initializer list containing matrix values.
   */
  Mat4(std::initializer_list<std::initializer_list<T>> values);

  /**
   * @brief Returns an identity matrix.
   * @return An identity matrix.
   */
  static Mat4 identity();

  /**
   * @brief Returns a translation matrix.
   * @param translation A `Vec3` containing translation values along X, Y, and Z
   * axes.
   * @return A translation matrix.
   */
  static Mat4 translate(const Vec3<T> &translation);

  /**
   * @brief Returns a scaling matrix.
   * @param scale A `Vec3` containing scaling factors along X, Y, and Z axes.
   * @return A scaling matrix.
   */
  static Mat4 scale(const Vec3<T> &scale);

  /**
   * @brief Returns an anisotropic scaling matrix.
   * @param scale A `Vec3` containing scaling factors along X, Y, and Z axes.
   * @return An anisotropic scaling matrix.
   */
  static Mat4 scale_aniso(const Vec3<T> &scale);

  /**
   * @brief Returns a Z-axis rotation matrix.
   * @param angle Rotation angle in radians.
   * @return A rotation matrix.
   */
  static Mat4 rotateZ(T angle);

  /**
   * @brief Returns an orthographic projection matrix.
   * @param left Left boundary of the view.
   * @param right Right boundary of the view.
   * @param bottom Bottom boundary of the view.
   * @param top Top boundary of the view.
   * @param near Near clipping plane.
   * @param far Far clipping plane.
   * @return An orthographic projection matrix.
   */
  static Mat4 ortho(T left, T right, T bottom, T top, T near, T far);

  /**
   * @brief Returns a perspective projection matrix.
   * @param fov Field of view in radians.
   * @param aspect Aspect ratio of the view.
   * @param near Near clipping plane.
   * @param far Far clipping plane.
   * @return A perspective projection matrix.
   */
  static Mat4 projection(T fov, T aspect, T near, T far);

  /**
   * @brief Returns a look-at matrix.
   * @param eye Camera position as a `Vec3`.
   * @param center Target position as a `Vec3`.
   * @param up Up vector as a `Vec3`.
   * @return A look-at matrix.
   */
  static Mat4 look_at(const Vec3<T> &eye, const Vec3<T> &center,
                      const Vec3<T> &up);

  /**
   * @brief Multiplies this matrix with another matrix.
   * @param other The other matrix.
   * @return The result of the multiplication.
   */
  Mat4 multiply(const Mat4 &other) const;

  /**
   * @brief Returns the transpose of this matrix.
   * @return The transposed matrix.
   */
  Mat4 transpose() const;

  /**
   * @brief Access element at specified row and column.
   * @param row The row index.
   * @param col The column index.
   * @return Reference to the element at the specified position.
   */
  T &at(size_t row, size_t col);

  /**
   * @brief Access element at specified row and column (const).
   * @param row The row index.
   * @param col The column index.
   * @return Const reference to the element at the specified position.
   */
  const T &at(size_t row, size_t col) const;
};

#endif // MAT_H
