
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
    layout (location = 1) in vec3 aColor;
    layout (location = 2) in vec2 aTexCoords;

    out vec3 color;
    out vec2 texCoords;

    uniform float scale;
    uniform mat4 projection;

    void main() {
        gl_Position = projection * vec4(aPos + aPos * scale, 1.0);
        color = aColor;
        texCoords = aTexCoords;
    }
)";

/**
 * @brief Default fragment shader source code.
 */
constexpr const char *default_fragment_shader = R"(
    #version 330 core
    out vec4 FragColor;

    in vec3 color;
    in vec2 texCoords;

    uniform sampler2D tex0;

    void main() {
      FragColor = texture(tex0, texCoords) * vec4(color, 1.0);
    }
)";

/**
 * @class Shader
 * @brief A class to manage OpenGL shaders.
 */
class Shader {
  GLuint m_id; ///< Shader program ID

  void compileErrors(unsigned int shader, const char *type);

public:
  /**
   * @brief Constructor for the Shader class.
   * @param vertex_source Source code for the vertex shader.
   * @param fragment_source Source code for the fragment shader.
   */
  Shader(const char *vertex_source = nullptr,
         const char *fragment_source = nullptr);

  /**
   * @brief Returns the ID of the shader program.
   * @return The ID of the shader program.
   */
  GLuint GetID();

  /**
   * @brief Activates the shader program.
   */
  void Activate() const;

  /**
   * @brief Deletes the shader program.
   */
  void Delete();
};

#endif // SHADER_H
