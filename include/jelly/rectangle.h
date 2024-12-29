#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <jelly/shape.h>

class Rectangle : public Shape {
  Vec2<float> m_size;

public:
  Rectangle(const Vec2<float> &position, const Vec2<float> &size,
            const Vec4<float> &color, bool filled = true)
      : Shape(position, color, filled), m_size(size) {}

  std::vector<Vec2<float>> getVertices() const override {
    return {
        m_position,                                         // bottom left
        {m_position.x + m_size.x, m_position.y},            // bottom right
        {m_position.x + m_size.x, m_position.y + m_size.y}, // top right
        {m_position.x, m_position.y + m_size.y},            // top left
    };
  }

  std::vector<GLuint> getIndices(GLuint startIndex) const override {
    if (m_filled) {
      return {
          startIndex, startIndex + 1, startIndex + 2,
          startIndex, startIndex + 2, startIndex + 3,
      };
    } else {
      return {
          startIndex,     startIndex + 1, // Bottom edge
          startIndex + 1, startIndex + 2, // Right edge
          startIndex + 2, startIndex + 3, // Top edge
          startIndex + 3, startIndex      // Left edge
      };
    }
  }
};

#endif // RECTANGLE_H
