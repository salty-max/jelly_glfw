/**
 * @file sprite.h
 *
 * @brief This file contains the definition of the Sprite class.
 */
#ifndef SPRITE_H
#define SPRITE_H

#include <vector>

#include <jelly/texture.h>
#include <jelly/vec.h>

/**
 * @brief A class to encapsulate a sprite.
 */
class Sprite {
  float m_width;
  float m_height;
  Vec3<float> m_position = Vec3<float>(0.0f, 0.0f, 0.0f);
  Vec3<float> m_scale = Vec3<float>(1.0f, 1.0f, 1.0f);
  Vec3<float> m_rotation = Vec3<float>(0.0f, 0.0f, 0.0f);
  Vec4<float> m_color = Vec4<float>(1.0f, 1.0f, 1.0f, 1.0f);
  Texture m_texture;

public:
  /**
   * @brief Constructs a Sprite object.
   *
   * @param texturePath The file path to the texture image.
   * @param width The width of the sprite.
   * @param height The height of the sprite.
   */
  Sprite(const char *texturePath,
         Vec4<float> color = Vec4<float>(1.0f, 1.0f, 1.0f, 1.0f), int width = 0,
         int height = 0);
  ~Sprite();

  /**
   * @brief Sets the position, scale, and rotation of the sprite.
   *
   * @param position The position of the sprite.
   */
  void setPosition(const Vec3<float> &position);

  /**
   * @brief Sets the scale of the sprite.
   *
   * @param scale The scale of the sprite.
   */
  void setScale(const Vec3<float> &scale);

  /**
   * @brief Sets the rotation of the sprite.
   *
   * @param rotation The rotation of the sprite.
   */
  void setRotation(const Vec3<float> &rotation);

  /**
   * @brief Gets the position of the sprite.
   *
   * @return The position of the sprite.
   */
  const Vec3<float> &getPosition() const;

  /**
   * @brief Gets the scale of the sprite.
   *
   * @return The scale of the sprite.
   */
  const Vec3<float> &getScale() const;

  /**
   * @brief Gets the rotation of the sprite.
   *
   * @return The rotation of the sprite.
   */
  const Vec3<float> &getRotation() const;

  /**
   * @brief Gets the width of the sprite.
   *
   * @return The width of the sprite.
   */
  float getWidth() const;

  /**
   * @brief Gets the height of the sprite.
   *
   * @return The height of the sprite.
   */
  float getHeight() const;

  /**
   * @brief Gets the size of the sprite.
   *
   * @return The size of the sprite.
   */
  Vec2<float> getSize() const;

  /**
   * @brief Gets the texture of the sprite.
   *
   * @return A reference to the texture.
   */
  const Texture &getTexture() const;

  /**
   * @brief Gets the color of the sprite.
   *
   * @return The color of the sprite.
   */
  const Vec4<float> &getColor() const;
};

#endif // SPRITE_H
