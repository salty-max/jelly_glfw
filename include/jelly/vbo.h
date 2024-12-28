#ifndef VBO_H
#define VBO_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>

/**
 * @class VBO
 * @brief A class to handle Vertex Buffer Objects (VBO) in OpenGL.
 *
 * This class provides methods to create, bind, unbind, and delete VBOs.
 */
class VBO {
  GLuint m_id;

public:
  /**
   * @brief Constructs a VBO object and generates a new VBO ID.
   */
  VBO();

  /**
   * @brief Constructs a VBO object and initializes it with the given vertices.
   *
   * @param vertices A pointer to the array of vertices.
   * @param size The size of the vertices array in bytes.
   */
  void Init(const void *vertices, GLsizeiptr size);

  /**
   * @brief Updates the VBO with new vertices.
   *
   * @param vertices A pointer to the array of vertices.
   * @param size The size of the vertices array in bytes.
   */
  void Update(const void *vertices, GLsizeiptr size);

  /**
   * @brief Binds the VBO.
   *
   * This method binds the VBO to the current OpenGL context.
   */
  void Bind() const;

  /**
   * @brief Unbinds the VBO.
   *
   * This method unbinds the VBO from the current OpenGL context.
   */
  void Unbind() const;

  /**
   * @brief Deletes the VBO.
   *
   * This method deletes the VBO and frees the associated resources.
   */
  void Delete();

  /**
   * @brief Gets the ID of the VBO.
   *
   * @return The ID of the VBO.
   */
  const GLuint getID() const;
};

#endif