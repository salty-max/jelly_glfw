#include <jelly/vao.h>
#include <jelly/utils.h>

VAO::VAO() : m_id(0) {}

void VAO::Init() { GL_CHECK(glGenVertexArrays(1, &m_id)); }

void VAO::Bind() const { GL_CHECK(glBindVertexArray(m_id)); }

void VAO::Unbind() const { GL_CHECK(glBindVertexArray(0)); }

void VAO::Delete() {
  if (m_id != 0) {
    Unbind();
    GL_CHECK(glDeleteVertexArrays(1, &m_id));
    m_id = 0; // Reset to prevent accidental re-deletion
  }
}

void VAO::LinkAttrib(VBO vbo, GLuint layout, GLuint numComponents, GLenum type,
                     GLsizeiptr stride, GLvoid *offset) {
  vbo.Bind();
  GL_CHECK(glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride,
                                 offset));
  GL_CHECK(glEnableVertexAttribArray(layout));
}

const GLuint VAO::getID() const { return m_id; }