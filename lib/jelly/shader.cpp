#include <iostream>

#include <jelly/shader.h>

Shader::Shader(const char *vertex_file_path, const char *fragment_file_path) {
  int success;
  GLchar *log;

  const char *vertex_source = default_vertex_shader;
  const char *fragment_source = default_fragment_shader;

  if (vertex_file_path) {
    vertex_source = read_file(vertex_file_path);
  }

  if (fragment_file_path) {
    fragment_source = read_file(fragment_file_path);
  }

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertex_source, nullptr);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, nullptr, log);
    std::cerr << "Error: Vertex shader compilation failed: " << log
              << std::endl;
  }

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragment_source, nullptr);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, nullptr, log);
    std::cerr << "Error: Fragment shader compilation failed: " << log
              << std::endl;
  }

  m_id = glCreateProgram();
  glAttachShader(m_id, vertexShader);
  glAttachShader(m_id, fragmentShader);

  glLinkProgram(m_id);
  glGetProgramiv(m_id, GL_LINK_STATUS, &success);

  if (!success) {
    glGetProgramInfoLog(m_id, 512, nullptr, log);
    std::cerr << "Error: Shader program linking failed: " << log << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void Shader::Activate() { glUseProgram(m_id); }

void Shader::Delete() { glDeleteProgram(m_id); }