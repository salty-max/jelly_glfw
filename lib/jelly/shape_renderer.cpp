#include <jelly/shape_renderer.h>

ShapeRenderer::ShapeRenderer(int windowWidth, int windowHeight, float scale)
    : m_projection(
          Mat4<float>::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f)) {}

ShapeRenderer::~ShapeRenderer() {}

void ShapeRenderer::initShaders() {
  std::cout << "Initializing shape shaders..." << std::endl;

  m_shapeShader.Compile(shape_vertex_shader, shape_fragment_shader);

  m_shapeShader.Activate();
  GLuint projectionLoc =
      glGetUniformLocation(m_shapeShader.GetID(), "projection");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, m_projection.value_ptr());

  std::cout << "Shape shaders initialized." << std::endl;
}

void ShapeRenderer::initBuffers() {
  m_vao.Init();
  m_vbo.Init(nullptr, MAX_SHAPE_BATCH_SIZE * 4 * sizeof(ShapeVertex));
  m_ebo.Init(nullptr, MAX_SHAPE_BATCH_SIZE * 6 * sizeof(GLuint));

  m_vao.Bind();
  m_vbo.Bind();
  m_ebo.Bind();

  m_vao.LinkAttrib(m_vbo, 0, 2, GL_FLOAT, sizeof(ShapeVertex),
                   (void *)offsetof(ShapeVertex, position));
  m_vao.LinkAttrib(m_vbo, 1, 4, GL_FLOAT, sizeof(ShapeVertex),
                   (void *)offsetof(ShapeVertex, color));

  m_vao.Unbind();
}

void ShapeRenderer::init() {
  initShaders();
  initBuffers();
}

void ShapeRenderer::begin() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  m_currentBatch.clear();
  m_indices.clear();
}

void ShapeRenderer::submit(Shape &shape) {
  auto vertices = shape.getVertices();
  auto indices = shape.getIndices(static_cast<GLuint>(m_currentBatch.size()));

  // Add vertices to the batch
  for (const auto &vertex : vertices) {
    m_currentBatch.push_back({vertex, shape.getColor()});
  }

  // Add indices to the batch
  m_indices.insert(m_indices.end(), indices.begin(), indices.end());

  // Flush if we exceed the maximum batch size
  if (m_currentBatch.size() / 4 >= MAX_SHAPE_BATCH_SIZE) {
    flush();
  }
}

void ShapeRenderer::flush() {
  if (m_currentBatch.empty()) {
    return;
  }

  m_vao.Bind();
  m_vbo.Update(m_currentBatch.data(),
               m_currentBatch.size() * sizeof(ShapeVertex));
  m_ebo.Update(m_indices.data(), m_indices.size() * sizeof(GLuint));

  m_shapeShader.Activate();

  glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()),
                 GL_UNSIGNED_INT, 0);

  m_vao.Unbind();

  m_currentBatch.clear();
  m_indices.clear();
}

void ShapeRenderer::end() { flush(); }

void ShapeRenderer::shutdown() {
  m_shapeShader.Delete();
  m_vbo.Delete();
  m_ebo.Delete();
  m_vao.Delete();
}
