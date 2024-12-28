#include <iostream>

#include <jelly/shader.h>

void Shader::compileErrors(unsigned int shader, const char *type) {
  int success;

  if (strcmp(type, "PROGRAM") != 0) {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
      GLchar log[1024];
      glGetShaderInfoLog(shader, 1024, nullptr, log);
      std::cerr << "Error: Shader compilation failed: " << log << std::endl;
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);

    if (!success) {
      GLchar log[1024];
      glGetProgramInfoLog(shader, 1024, nullptr, log);
      std::cerr << "Error: Shader linking failed: " << log << std::endl;
    }
  }
}

Shader::Shader() : m_id(0) {}

void Shader::Compile(const char *vertex_source, const char *fragment_source) {
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertex_source, nullptr);
  glCompileShader(vertexShader);
  compileErrors(vertexShader, "VERTEX");

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragment_source, nullptr);
  glCompileShader(fragmentShader);
  compileErrors(fragmentShader, "FRAGMENT");

  m_id = glCreateProgram();
  glAttachShader(m_id, vertexShader);
  glAttachShader(m_id, fragmentShader);

  glLinkProgram(m_id);
  compileErrors(m_id, "PROGRAM");

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

GLuint Shader::GetID() { return m_id; }

void Shader::Activate() const { glUseProgram(m_id); }

void Shader::Delete() { glDeleteProgram(m_id); }