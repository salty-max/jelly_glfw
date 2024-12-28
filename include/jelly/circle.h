#ifndef CIRCLE_H
#define CIRCLE_H

#include <jelly/shape.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/**
 * @brief Circle shape class.
 *
 * Represents a circle with a position, radius, and color.
 */
class Circle : public Shape {
  float m_radius;
  size_t m_segments;

public:
  Circle(const Vec2<float> &position, float radius, const Vec4<float> &color,
         size_t segments = 32)
      : Shape(position, color), m_radius(radius), m_segments(segments) {}

  std::vector<Vec2<float>> getVertices() const override {
    std::vector<Vec2<float>> vertices;
    vertices.emplace_back(m_position); // Center of the circle

    for (size_t i = 0; i <= m_segments; ++i) {
      float angle = i * 2.0f * M_PI / m_segments;
      vertices.emplace_back(m_position.x + m_radius * cos(angle),
                            m_position.y + m_radius * sin(angle));
    }

    return vertices;
  }

  std::vector<GLuint> getIndices(GLuint startIndex) const override {
    std::vector<GLuint> indices;

    for (size_t i = 1; i <= m_segments; ++i) {
      indices.insert(indices.end(), {
                                        startIndex,
                                        startIndex + static_cast<GLuint>(i),
                                        startIndex + static_cast<GLuint>(i + 1),
                                    });
    }

    return indices;
  }
};

#endif // CIRCLE_H
