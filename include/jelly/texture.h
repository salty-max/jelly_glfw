
/**
 * @file texture.h
 * @brief This file contains the definition of the Texture class.
 */
#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/gl.h>

#include <jelly/image.h>
#include <jelly/shader.h>

/**
 * @brief A class to encapsulate an OpenGL texture.
 *
 * This class provides methods to create, bind, unbind, delete, and set the
 * texture parameters.
 */
class Texture {
  GLuint m_id;
  GLenum m_type;

public:
  /**
   * @brief Constructs a Texture object and loads a texture from a file.
   *
   * @param path The file path to the texture image.
   * @param type The type of the texture (default is GL_TEXTURE_2D).
   * @param slot The texture slot to bind the texture to.
   * @param format The format of the texture image.
   * @param pixelType The data type of the pixel data.
   */
  Texture(const char *path, GLenum texType = GL_TEXTURE_2D,
          GLenum slot = GL_TEXTURE0, GLenum format = GL_RGBA,
          GLenum pixelType = GL_UNSIGNED_BYTE);

  /**
   * @brief Sets the texture unit for a shader.
   *
   * @param shader The shader to set the texture unit for.
   * @param uniform The name of the uniform variable in the shader.
   * @param unit The texture unit to set.
   */
  void texUnit(Shader shader, const char *uniform, GLuint unit);

  /**
   * @brief Binds the texture.
   *
   * This method binds the texture, making it the current texture in use.
   */
  void Bind() const;

  /**
   * @brief Unbinds the texture.
   *
   * This method unbinds the texture, making no texture currently bound.
   */
  void Unbind() const;

  /**
   * @brief Deletes the texture.
   *
   * This method deletes the texture, freeing up the associated resources.
   */
  void Delete();
};

#endif // TEXTURE_H