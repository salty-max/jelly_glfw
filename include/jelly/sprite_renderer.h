#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <iostream>
#include <vector>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <jelly/shader.h>
#include <jelly/sprite.h>
#include <jelly/vao.h>
#include <jelly/vbo.h>
#include <jelly/ebo.h>
#include <jelly/vec.h>
#include <jelly/mat.h>

/**
 * @brief The maximum number of sprites per batch.
 */
const size_t MAX_SPRITE_BATCH_SIZE = 10000;

/**
 * @brief A struct to represent a sprite vertex.
 *
 * This struct contains the position, UVs, and color of a vertex.
 */
struct SpriteVertex {
  Vec2<float> position;
  Vec2<float> uvs;
  Vec4<float> color;
};

/**
 * @class SpriteRenderer
 *
 * @brief A class to manage rendering batched sprites.
 */
class SpriteRenderer {
  int m_windowWidth;
  int m_windowHeight;
  float m_scale;
  Shader m_spriteShader;
  VAO m_vao;
  VBO m_vbo;
  EBO m_ebo;

  std::vector<SpriteVertex> m_currentBatch;
  std::vector<GLuint> m_indices;
  const Texture *m_currentTexture = nullptr;

  Mat4<float> m_projection;

  /**
   * @brief Initializes the shader program.
   *
   * This method compiles and sets up the shader program for rendering sprites.
   */
  void initShaders();

  /**
   * @brief Initializes the vertex array and buffer objects.
   *
   * This method sets up the VAO, VBO, and EBO for storing and rendering vertex
   * data.
   */
  void initBuffers();

  /**
   * @brief Flushes the current batch of sprites to the screen.
   *
   * This method uploads the vertex data to the GPU and issues a draw call.
   */
  void flush();

public:
  /**
   * @brief Constructs a SpriteRenderer object.
   *
   * @param windowWidth The width of the window.
   * @param windowHeight The height of the window.
   * @param scale The scale of the window.
   */
  SpriteRenderer(int windowWidth, int windowHeight, float scale);

  /**
   * @brief Destructs a SpriteRenderer object.
   */
  ~SpriteRenderer();

  /**
   * @brief Initializes the SpriteRenderer.
   *
   * This method sets up shaders, buffers, and the projection matrix.
   */
  void init();

  /**
   * @brief Begins a new sprite rendering batch.
   *
   * This method prepares the renderer for a new frame.
   */
  void begin();

  /**
   * @brief Submits a sprite to the current batch.
   *
   * @param sprite The sprite to submit.
   */
  void submit(const Sprite &sprite);

  /**
   * @brief Ends the current sprite rendering batch.
   *
   * This method flushes the current batch and renders it.
   */
  void end();

  /**
   * @brief Shuts down the SpriteRenderer.
   *
   * This method cleans up the resources used by the renderer.
   */
  void shutdown();
};

#endif // SPRITE_RENDERER_H