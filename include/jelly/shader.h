
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
constexpr const char *quad_vertex_shader = R"(
   #version 460 core
    layout(location = 0) in vec2 a_pos;
    layout(location = 1) in vec2 a_uv;
    layout(location = 2) in vec4 a_color;
    layout(location = 3) in float a_texIndex;

    out vec2 v_uv;
    out vec4 v_color;
    out float v_texIndex;

    uniform mat4 projection;

    void main() {
        v_uv = a_uv;
        v_color = a_color;
        v_texIndex = a_texIndex;
        gl_Position = projection * vec4(a_pos, 0.0, 1.0);
    }

)";

/**
 * @brief Default fragment shader source code.
 */
constexpr const char *quad_fragment_shader = R"(
    #version 460 core
    out vec4 fragColor;

    in vec2 v_uv;
    in vec4 v_color;
    in float v_texIndex;

    uniform sampler2D textures[32]; // Support up to 32 texture slots

    void main() {
        if (v_texIndex < 0.0) { // Untextured
            fragColor = v_color;
        } else { // Textured
            int index = int(v_texIndex);
            fragColor = texture(textures[index], v_uv) * v_color;
        }
    }

)";

constexpr const char *circle_vertex_shader = R"(
    #version 460 core

    layout(location = 0) in vec2 a_pos;      // Position of the vertex
    layout(location = 1) in vec2 a_uv;       // UV coordinates (not used here)
    layout(location = 2) in vec4 a_color;    // Per-instance color
    layout(location = 3) in vec2 a_center;   // Per-instance circle center
    layout(location = 4) in float a_radius;  // Per-instance circle radius

    out vec2 fragUV;       // Pass normalized position
    out vec4 fragColor;    // Pass color to fragment shader
    out vec2 fragCenter;   // Pass transformed circle center
    out float fragRadius;  // Pass radius to fragment shader

    uniform mat4 projection;

    void main() {
        vec4 worldPos = projection * vec4(a_pos, 0.0, 1.0);
        fragUV = a_pos;           // Object-space coordinates
        fragColor = a_color;      // Circle color
        fragCenter = (projection * vec4(a_center, 0.0, 1.0)).xy; // Transformed center
        fragRadius = a_radius;    // Circle radius (unchanged)

        gl_Position = worldPos;
    }
)";

constexpr const char *circle_fragment_shader = R"(
    #version 460 core

    in vec2 fragUV;       // Object-space UV coordinates
    in vec4 fragColor;    // Circle color
    in vec2 fragCenter;   // Transformed circle center
    in float fragRadius;  // Circle radius

    out vec4 fragColorOut;  // Output color

    void main() {
        float dist = length(fragUV - fragCenter);  // Distance to the center
        float alpha = smoothstep(fragRadius - 0.01, fragRadius, dist); // Anti-aliasing
        if (dist > fragRadius) discard; // Outside the circle boundary
        fragColorOut = vec4(fragColor.rgb, 1.0);
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
