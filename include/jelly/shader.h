
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
    #version 460 core
    layout (location = 0) in vec3 a_pos;
    layout (location = 1) in vec2 a_uvs;

    out vec2 v_uvs;

    uniform mat4 projection;
    uniform mat4 view;

    void main() {
        v_uvs = a_uvs;
        gl_Position = projection * view * vec4(a_pos, 1.0);
    }
)";

/**
 * @brief Default fragment shader source code.
 */
constexpr const char *default_fragment_shader = R"(
    #version 460 core
    layout (location = 0) out vec4 frag_color;

    in vec2 v_uvs;

    layout (binding = 0) uniform sampler2D texture_id;
    layout (location = 1) uniform vec4 color;

    void main() {
        frag_color = texture(texture_id, v_uvs) * color;
    }
)";

/**
 * @brief Batch quad vertex shader source code.
 */
constexpr const char *batch_quad_vertex_shader = R"(
    #version 460 core
    layout (location = 0) in vec2 a_pos;
    layout (location = 1) in vec2 a_uvs;
    layout (location = 2) in vec4 a_color;

    out vec2 v_uvs;
    out vec4 v_color;

    uniform mat4 projection;

    void main() {
        v_color = a_color;
        v_uvs = a_uvs;
        gl_Position = projection * vec4(a_pos, 0.0, 1.0);
    }
)";

/**
 * @brief Batch quad fragment shader source code.
 */
constexpr const char *batch_quad_fragment_shader = R"(
    #version 460 core
    layout (location = 0) out vec4 o_color;

    in vec2 v_uvs;
    in vec4 v_color;

    layout (binding = 0) uniform sampler2D texture_slot;

    void main() {
        o_color = texture(texture_slot, v_uvs) * v_color;
    }
)";

/**
 * @brief Shape vertex shader source code.
 */
constexpr const char *shape_vertex_shader = R"(
    #version 460 core
    layout (location = 0) in vec2 a_pos;
    layout (location = 1) in vec4 a_color;

    out vec4 v_color;

    uniform mat4 projection;

    void main() {
        v_color = a_color;
        gl_Position = projection * vec4(a_pos.xy, 0.0, 1.0);
    }
)";

/**
 * @brief Shape fragment shader source code.
 */
constexpr const char *shape_fragment_shader = R"(
    #version 460 core
    layout (location = 0) out vec4 frag_color;

    in vec4 v_color;

    void main() {
        frag_color = v_color;
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
  Shader();

  /**
   * @brief Returns the ID of the shader program.
   * @return The ID of the shader program.
   */
  GLuint GetID();

  /**
   * @brief Compiles the shader program.
   * @param vertex_source The source code for the vertex shader.
   * @param fragment_source The source code for the fragment shader.
   */
  void Compile(const char *vertex_path, const char *fragment_source);

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
