#ifndef SHAPE_H
#define SHAPE_H

#include <vector>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <jelly/vec.h>

/**
 * @brief Base class for shapes.
 *
 * Provides a common interface for all shapes.
 */
class Shape {
protected:
  Vec2<float> m_position;
  Vec4<float> m_color;

public:
  Shape(const Vec2<float> &position,
        const Vec4<float> &color = Vec4<float>(1.0f, 1.0f, 1.0f, 1.0f))
      : m_position(position), m_color(color) {}

  virtual ~Shape() = default;

  /**
   * @brief Generates the vertex data for the shape.
   *
   * @return A vector of vertices.
   */
  virtual std::vector<Vec2<float>> getVertices() const = 0;

  /**
   * @brief Generates the indices for the shape.
   *
   * @param startIndex The starting index for the shape.
   * @return A vector of indices.
   */
  virtual std::vector<GLuint> getIndices(GLuint startIndex) const = 0;

  const Vec2<float> &getPosition() const { return m_position; }
  const Vec4<float> &getColor() const { return m_color; }
};

#endif // SHAPE_H
