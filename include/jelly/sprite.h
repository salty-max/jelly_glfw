#ifndef SPRITE_H
#define SPRITE_H

#include <jelly/texture.h>
#include <jelly/vao.h>
#include <jelly/vbo.h>
#include <jelly/ebo.h>

class Sprite {
  VAO m_vao;
  VBO m_vbo;
  EBO m_ebo;
  Texture m_texture;

public:
  Sprite(const char *texturePath, float width, float height);
  ~Sprite();

  void draw() const;
};

#endif // SPRITE_H
