#ifndef VERTEX_H
#define VERTEX_H

#include <jelly/vec.h>

/**
 * @brief A struct representing a vertex.
 */
struct Vertex {
  Vec3<float> position;  ///< Position of the vertex
  Vec3<float> color;     ///< Color of the vertex
  Vec2<float> texCoords; ///< Texture coordinates of the vertex
};

#endif // VERTEX_H