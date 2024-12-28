#include <jelly/texture.h>

Texture::Texture(const char *path, GLenum texType, GLenum slot, GLenum format,
                 GLenum pixelType) {
  m_type = texType;
  m_slot = slot;

  int width, height, channels;
  unsigned char *data = load_image(path, width, height, channels);

  m_width = width;
  m_height = height;

  if (!data) {
    std::cerr << "Failed to load texture: " << path << std::endl;
    return;
  }

  std::cout << "Loaded texture: " << path << " [Width: " << width
            << ", Height: " << height << ", Channels: " << channels << "]"
            << std::endl;

  glGenTextures(1, &m_id);
  glActiveTexture(m_slot);
  glBindTexture(m_type, m_id);

  glTexParameteri(m_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(m_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexParameteri(m_type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(m_type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glTexImage2D(m_type, 0, format, width, height, 0, format, pixelType, data);
  // glGenerateMipmap(m_type);

  free_image(data);
  glBindTexture(m_type, 0);
}

const void Texture::texUnit(Shader shader, const char *uniform,
                            GLuint unit) const {
  GLint location = glGetUniformLocation(shader.GetID(), uniform);
  if (location == -1) {
    std::cerr << "Error: Texture uniform '" << uniform
              << "' not found in shader!" << std::endl;
  }
  glUniform1i(location, unit);
}

void Texture::Bind() const {
  glBindTexture(m_type, m_id);
  GLint boundTexture;
  glGetIntegerv(GL_TEXTURE_BINDING_2D, &boundTexture);
  if (boundTexture != static_cast<GLint>(m_id)) {
    std::cerr << "[Texture] Mismatch! Expected: " << m_id
              << ", Bound: " << boundTexture << std::endl;
  } else {
    std::cout << "[Texture] Bound texture ID: " << m_id
              << " to slot 0 (GL_TEXTURE0)." << std::endl;
  }
}

void Texture::Unbind() const { glBindTexture(m_type, 0); }

void Texture::Delete() { glDeleteTextures(1, &m_id); }

int Texture::getWidth() const { return m_width; }

int Texture::getHeight() const { return m_height; }

const GLuint Texture::getID() const { return m_id; }

const GLenum Texture::getType() const { return m_type; }

const GLenum Texture::getSlot() const { return m_slot; }