#include <jelly/ebo.h>
#include <jelly/utils.h>

EBO::EBO() : m_id(0) {}

void EBO::Init(const void *indices, GLsizeiptr size) {
  GL_CHECK(glGenBuffers(1, &m_id));
  GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
  GL_CHECK(
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW));
}

void EBO::Update(const void *indices, GLsizeiptr size) {
  Bind();
  GL_CHECK(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, indices));
}

void EBO::Bind() const {
  GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
}

void EBO::Unbind() const { GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); }

void EBO::Delete() {
  if (m_id != 0) {
    Unbind();
    GL_CHECK(glDeleteBuffers(1, &m_id));
    m_id = 0; // Reset to prevent accidental re-deletion
  }
}

const GLuint EBO::getID() const { return m_id; }
