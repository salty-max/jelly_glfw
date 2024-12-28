#include <jelly/sprite.h>
#include <jelly/game_context.h>

Sprite::Sprite(const char *texturePath, Vec4<float> color, int width,
               int height)
    : m_texture(texturePath) {
  m_width = width == 0 ? m_texture.getWidth() : width;
  m_height = height == 0 ? m_texture.getHeight() : height;
}

Sprite::~Sprite() { m_texture.Delete(); }

void Sprite::setPosition(const Vec3<float> &position) { m_position = position; }

void Sprite::setScale(const Vec3<float> &scale) { m_scale = scale; }

void Sprite::setRotation(const Vec3<float> &rotation) { m_rotation = rotation; }

const Vec3<float> &Sprite::getPosition() const { return m_position; }

const Vec3<float> &Sprite::getScale() const { return m_scale; }

const Vec3<float> &Sprite::getRotation() const { return m_rotation; }

float Sprite::getWidth() const { return m_width; }

float Sprite::getHeight() const { return m_height; }

Vec2<float> Sprite::getSize() const { return Vec2<float>(m_width, m_height); }

const Texture &Sprite::getTexture() const { return m_texture; }

const Vec4<float> &Sprite::getColor() const { return m_color; }
