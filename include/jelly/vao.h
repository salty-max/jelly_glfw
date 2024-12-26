/**
 * @file vao.h
 * @brief This file contains the definition of the VAO (Vertex Array Object)
 * class.
 */
#ifndef VAO_H
#define VAO_H

#include <glad/gl.h>
#include <jelly/vbo.h>

/**
 * @class VAO
 * @brief A class to encapsulate an OpenGL Vertex Array Object (VAO).
 *
 * This class provides methods to create, bind, unbind, delete, and link a
 * Vertex Buffer Object (VBO) to the VAO.
 */
class VAO {
  GLuint m_id;

public:
  /**
   * @brief Constructs a VAO object and generates a new VAO ID.
   */
  VAO();

  /**
   * @brief Binds the VAO.
   *
   * This method binds the VAO, making it the current VAO in use.
   */
  void Bind() const;

  /**
   * @brief Unbinds the VAO.
   *
   * This method unbinds the VAO, making no VAO currently bound.
   */
  void Unbind() const;

  /**
   * @brief Deletes the VAO.
   *
   * This method deletes the VAO, freeing up the associated resources.
   */
  void Delete();

  /**
   * @brief Links a Vertex Buffer Object (VBO) to the VAO.
   *
   * @param vbo The VBO to be linked.
   * @param layout The layout location to which the VBO should be linked.
   *
   * This method links a VBO to the VAO at the specified layout location.
   */
  void LinkAttrib(VBO vbo, GLuint layout, GLuint numComponents, GLenum type,
                  GLsizeiptr stride, GLvoid *offset);
};

#endif // VAO_H
