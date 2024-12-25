
/**
 * @file shader.h
 * @brief This file contains the Shader class and default shader source code.
 */

#ifndef SHADER_H
#define SHADER_H

#include <glad/gl.h>

#include <jelly/io.h>

/**
 * @brief Default vertex shader source code.
 */
constexpr const char *default_vertex_shader = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    void main() {
        gl_Position = vec4(aPos, 1.0);
    }
)";

/**
 * @brief Default fragment shader source code.
 */
constexpr const char *default_fragment_shader = R"(
    #version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0, 0.5, 0.2, 1.0);
    }
)";

/**
 * @class Shader
 * @brief A class to manage OpenGL shaders.
 */
class Shader {
  GLuint m_id; ///< Shader program ID

public:
  /**
   * @brief Constructor for the Shader class.
   * @param vertex_source Source code for the vertex shader.
   * @param fragment_source Source code for the fragment shader.
   */
  Shader(const char *vertex_source = nullptr,
         const char *fragment_source = nullptr);

  /**
   * @brief Activates the shader program.
   */
  void Activate();

  /**
   * @brief Deletes the shader program.
   */
  void Delete();
};

#endif // SHADER_H
