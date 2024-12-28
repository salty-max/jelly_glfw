/**
 * @file shape_renderer.h
 *
 * @brief This file contains the definition of the ShapeRenderer class.
 */
#ifndef SHAPE_RENDERER_H
#define SHAPE_RENDERER_H

#include <iostream>
#include <vector>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <jelly/shader.h>
#include <jelly/shape.h>
#include <jelly/vao.h>
#include <jelly/vbo.h>
#include <jelly/ebo.h>
#include <jelly/vec.h>
#include <jelly/mat.h>

/**
 * @brief The maximum number of shapes (quads) per batch.
 */
const size_t MAX_SHAPE_BATCH_SIZE = 10000;

/**
 * @brief A struct to represent a shape vertex.
 *
 * This struct contains the position and color of a vertex.
 */
struct ShapeVertex {
  Vec2<float> position;
  Vec4<float> color;
};

/**
 * @class ShapeRenderer
 *
 * @brief A class to manage rendering batched shapes (rectangles, lines,
 * triangles).
 */
class ShapeRenderer {
  int m_windowWidth;
  int m_windowHeight;
  float m_scale;
  Shader m_shapeShader;
  VAO m_vao;
  VBO m_vbo;
  EBO m_ebo;

  std::vector<ShapeVertex> m_currentBatch;
  std::vector<GLuint> m_indices;

  Mat4<float> m_projection;

  /**
   * @brief Initializes the shader program.
   *
   * This method compiles and sets up the shader program for rendering shapes.
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
   * @brief Flushes the current batch of shapes to the screen.
   *
   * This method uploads the vertex data to the GPU and issues a draw call.
   */
  void flush();

public:
  /**
   * @brief Constructs a ShapeRenderer object.
   */
  ShapeRenderer(int windowWidth, int windowHeight, float scale);

  /**
   * @brief Destructs a ShapeRenderer object.
   */
  ~ShapeRenderer();

  /**
   * @brief Initializes the ShapeRenderer.
   *
   * This method sets up shaders, buffers, and the projection matrix.
   */
  void init();

  /**
   * @brief Begins a new shape rendering batch.
   *
   * This method prepares the renderer for a new frame.
   */
  void begin();

  /**
   * @brief Submits a rectangle to the current batch.
   *
   * @param shape The shape to submit.
   */
  void submit(Shape &shape);

  /**
   * @brief Ends the current shape rendering batch.
   *
   * This method flushes the current batch and renders it.
   */
  void end();

  /**
   * @brief Shuts down the ShapeRenderer.
   *
   * This method cleans up the resources used by the renderer.
   */
  void shutdown();
};

#endif // SHAPE_RENDERER_H
