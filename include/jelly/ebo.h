
/**
 * @file ebo.h
 * @brief This file contains the definition of the EBO (Element Buffer Object)
 * class.
 */

#ifndef EBO_H
#define EBO_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>

/**
 * @class EBO
 * @brief A class to encapsulate an OpenGL Element Buffer Object (EBO).
 */
class EBO {
  GLuint m_id; ///< The ID of the EBO.

public:
  /**
   * @brief Constructs an EBO object.
   */
  EBO();

  /**
   * @brief Initializes the EBO with the given indices.
   * @param indices A pointer to the indices data.
   * @param size The size of the indices data in bytes.
   */
  void Init(const void *indices, GLsizeiptr size);

  /**
   * @brief Updates the EBO with new indices.
   * @param indices A pointer to the indices data.
   * @param size The size of the indices data in bytes.
   */
  void Update(const void *indices, GLsizeiptr size);

  /**
   * @brief Binds the EBO.
   */
  void Bind() const;

  /**
   * @brief Unbinds the EBO.
   */
  void Unbind() const;

  /**
   * @brief Deletes the EBO.
   */
  void Delete();

  /**
   * @brief Gets the ID of the EBO.
   * @return The ID of the EBO.
   */
  const GLuint getID() const;
};

#endif // EBO_H