#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <jelly/shape.h>

/**
 * @brief Rectangle shape class.
 *
 * Represents a rectangle with a position, size, and color.
 */
class Rectangle : public Shape {
  Vec2<float> m_size;

public:
  Rectangle(const Vec2<float> &position, const Vec2<float> &size,
            const Vec4<float> &color)
      : Shape(position, color), m_size(size) {}

  std::vector<Vec2<float>> getVertices() const override {
    return {
        m_position,                                         // bottom left
        {m_position.x + m_size.x, m_position.y},            // bottom right
        {m_position.x + m_size.x, m_position.y + m_size.y}, // top right
        {m_position.x, m_position.y + m_size.y},            // top left
    };
  }

  std::vector<GLuint> getIndices(GLuint startIndex) const override {
    return {
        startIndex, startIndex + 1, startIndex + 2,
        startIndex, startIndex + 2, startIndex + 3,
    };
  }
};

#endif // RECTANGLE_H
