#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <glad/gl.h>
#include <jelly/vec.h>

class Shape {
protected:
  Vec2<float> m_position;
  Vec4<float> m_color;
  bool m_filled; // New field to specify if the shape is filled

public:
  Shape(const Vec2<float> &position,
        const Vec4<float> &color = Vec4<float>(1.0f, 1.0f, 1.0f, 1.0f),
        bool filled = true) // Default to filled shapes
      : m_position(position), m_color(color), m_filled(filled) {}

  virtual ~Shape() = default;

  virtual std::vector<Vec2<float>> getVertices() const = 0;
  virtual std::vector<GLuint> getIndices(GLuint startIndex) const = 0;

  bool isFilled() const { return m_filled; }
  const Vec2<float> &getPosition() const { return m_position; }
  const Vec4<float> &getColor() const { return m_color; }
};

#endif // SHAPE_H
