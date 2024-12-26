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

Shader::Shader(const char *vertex_file_path, const char *fragment_file_path) {
  const char *vertex_source = default_vertex_shader;
  const char *fragment_source = default_fragment_shader;

  if (vertex_file_path) {
    std::string vert_data = read_file(vertex_file_path);
    vertex_source = vert_data.c_str();
  }

  if (fragment_file_path) {
    std::string frag_data = read_file(fragment_file_path);
    fragment_source = frag_data.c_str();
  }

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