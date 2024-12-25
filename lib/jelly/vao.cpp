#include <jelly/vao.h>

VAO::VAO() { glGenVertexArrays(1, &m_id); }

void VAO::Bind() { glBindVertexArray(m_id); }

void VAO::Unbind() { glBindVertexArray(0); }

void VAO::Delete() { glDeleteVertexArrays(1, &m_id); }

void VAO::LinkVBO(VBO vbo, GLuint layout) {
  vbo.Bind();
  glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (GLvoid *)0);
  glEnableVertexAttribArray(layout);
  vbo.Unbind();
}