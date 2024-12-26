#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <memory>

#include <glad/gl.h>
#include <jelly/shader.h>
#include <jelly/mat.h>

class Renderer {
private:
  int m_windowWidth;                       ///< Width of the window
  int m_windowHeight;                      ///< Height of the window
  std::unique_ptr<Shader> m_defaultShader; ///< Default shader for rendering
  Mat4<float> m_projectionMatrix;          ///< Projection matrix for rendering

public:
  Renderer(int windowWidth, int windowHeight);

  /**
   * @brief Initializes the default shader.
   */
  void init_shaders();

  /**
   * @brief Begins the rendering process for a frame.
   */
  void begin();

  /**
   * @brief Ends the rendering process for a frame.
   */
  void end();

  /**
   * @brief Updates the projection matrix (e.g., on window resize).
   */
  void updateProjection(int windowWidth, int windowHeight);

  /**
   * @brief Gets the default shader.
   * @return Reference to the default shader.
   */
  Shader &getDefaultShader();

  /**
   * @brief Cleans up resources.
   */
  void cleanup();
};

#endif // RENDERER_H
