#include <jelly/texture.h>

Texture::Texture(const char *path, GLenum texType, GLenum slot, GLenum format,
                 GLenum pixelType) {
  m_type = texType;

  int width, height, channels;
  unsigned char *data = load_image(path, width, height, channels);

  glGenTextures(1, &m_id);
  glActiveTexture(slot);
  glBindTexture(m_type, m_id);

  glTexParameteri(m_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  glTexParameteri(m_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexParameteri(m_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(m_type, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexImage2D(m_type, 0, format, width, height, 0, format, pixelType, data);
  glGenerateMipmap(m_type);

  free_image(data);
  glBindTexture(m_type, 0);
}

void Texture::texUnit(Shader shader, const char *uniform, GLuint unit) {
  glUniform1i(glGetUniformLocation(shader.GetID(), uniform), unit);
}

void Texture::Bind() const { glBindTexture(m_type, m_id); }

void Texture::Unbind() const { glBindTexture(m_type, 0); }

void Texture::Delete() { glDeleteTextures(1, &m_id); }