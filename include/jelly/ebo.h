
/**
 * @file ebo.h
 * @brief This file contains the definition of the EBO (Element Buffer Object)
 * class.
 */

#ifndef EBO_H
#define EBO_H

#include <glad/gl.h>

/**
 * @class EBO
 * @brief A class to encapsulate an OpenGL Element Buffer Object (EBO).
 */
class EBO {
  GLuint m_id; ///< The ID of the EBO.

public:
  /**
   * @brief Constructs an EBO and initializes it with the given indices.
   * @param indices A pointer to the indices data.
   * @param size The size of the indices data in bytes.
   */
  EBO(GLuint *indices, GLsizeiptr size);

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
};

#endif // EBO_H