#include <jelly/vao.h>

VAO::VAO() { glGenVertexArrays(1, &m_id); }

void VAO::Bind() const { glBindVertexArray(m_id); }

void VAO::Unbind() const { glBindVertexArray(0); }

void VAO::Delete() { glDeleteVertexArrays(1, &m_id); }

void VAO::LinkAttrib(VBO vbo, GLuint layout, GLuint numComponents, GLenum type,
                     GLsizeiptr stride, GLvoid *offset) {
  vbo.Bind();
  glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
  glEnableVertexAttribArray(layout);
  vbo.Unbind();
}