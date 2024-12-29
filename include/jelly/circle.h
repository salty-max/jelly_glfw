#ifndef CIRCLE_H
#define CIRCLE_H

#include <jelly/shape.h>
#include <cmath>
#include <vector>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Circle : public Shape {
  float m_radius;
  int m_segments;

public:
  Circle(const Vec2<float> &position, float radius, bool filled = true,
         const Vec4<float> &color = Vec4<float>(1.0f, 1.0f, 1.0f, 1.0f),
         int segments = 36)
      : Shape(position, color, filled), m_radius(radius), m_segments(segments) {
  }

  std::vector<Vec2<float>> getVertices() const override {
    std::vector<Vec2<float>> vertices;

    float angleIncrement = 2.0f * M_PI / m_segments;
    for (int i = 0; i <= m_segments; ++i) {
      float angle = i * angleIncrement;
      vertices.push_back({
          m_position.x + m_radius * static_cast<float>(cos(angle)),
          m_position.y + m_radius * static_cast<float>(sin(angle)),
      });
    }

    return vertices;
  }

  std::vector<GLuint> getIndices(GLuint startIndex) const override {
    std::vector<GLuint> indices;

    if (m_filled) {
      // Generate triangles for filled circle
      for (int i = 1; i < m_segments; ++i) {
        indices.push_back(startIndex);         // Center vertex
        indices.push_back(startIndex + i);     // Current edge vertex
        indices.push_back(startIndex + i + 1); // Next edge vertex
      }
      // Close the circle
      indices.push_back(startIndex);              // Center vertex
      indices.push_back(startIndex + m_segments); // Last edge vertex
      indices.push_back(startIndex + 1);          // First edge vertex
    } else {
      // Generate line segments for outlined circle
      for (int i = 0; i < m_segments; ++i) {
        indices.push_back(startIndex + i); // Current edge vertex
        indices.push_back(startIndex + (i + 1) % m_segments); // Next edge
      }
    }

    return indices;
  }

  float getRadius() const { return m_radius; }
  int getSegments() const { return m_segments; }
};

#endif // CIRCLE_H
