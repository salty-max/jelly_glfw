#include <jelly/vbo.h>
#include <jelly/utils.h>

VBO::VBO() : m_id(0) {}

void VBO::Init(const void *vertices, GLsizeiptr size) {
  GL_CHECK(glGenBuffers(1, &m_id));
  GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_id));
  GL_CHECK(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW));
}

void VBO::Update(const void *vertices, GLsizeiptr size) {
  Bind();
  GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices));
}

void VBO::Bind() const { GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_id)); }

void VBO::Unbind() const { GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0)); }

void VBO::Delete() {
  if (m_id != 0) {
    Unbind();
    GL_CHECK(glDeleteBuffers(1, &m_id));
    m_id = 0; // Reset to prevent accidental re-deletion
  }
}

const GLuint VBO::getID() const { return m_id; }
