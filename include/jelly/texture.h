
/**
 * @file texture.h
 * @brief This file contains the definition of the Texture class.
 */
#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>

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
  GLenum m_slot;
  int m_width;
  int m_height;

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
  const void texUnit(Shader shader, const char *uniform, GLuint unit) const;

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

  /**
   * @brief Gets the width of the texture.
   *
   * @return The width of the texture.
   */
  int getWidth() const;

  /**
   * @brief Gets the height of the texture.
   *
   * @return The height of the texture.
   */
  int getHeight() const;

  /**
   * @brief Gets the ID of the texture.
   *
   * @return The ID of the texture.
   */
  const GLuint getID() const;

  /**
   * @brief Gets the type of the texture.
   *
   * @return The type of the texture.
   */
  const GLenum getType() const;

  /**
   * @brief Gets the slot of the texture.
   *
   * @return The slot of the texture.
   */
  const GLenum getSlot() const;
};

#endif // TEXTURE_H