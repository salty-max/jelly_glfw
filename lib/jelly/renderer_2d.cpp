#include <jelly/renderer_2d.h>

Renderer2D::Renderer2D(int windowWidth, int windowHeight, float scale)
    : m_windowWidth(windowWidth), m_windowHeight(windowHeight), m_scale(scale),
      m_projection(Mat4<float>::ortho(0.0f, static_cast<float>(windowWidth),
                                      static_cast<float>(windowHeight), 0.0f,
                                      -1.0f, 1.0f)) {}

Renderer2D::~Renderer2D() {}

void Renderer2D::init() {
  std::cout << "Initializing 2D Renderer..." << std::endl;

  initQuadShaders();
  initQuadBuffers();

  initCircleShaders();
  initCircleBuffers();

  std::cout << "2D Renderer initialized." << std::endl;
}

void Renderer2D::initQuadShaders() {
  m_quadShader.Compile(quad_vertex_shader, quad_fragment_shader);
  m_quadShader.Activate();
  GLuint projectionLoc =
      glGetUniformLocation(m_quadShader.GetID(), "projection");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, m_projection.value_ptr());
}

void Renderer2D::initQuadBuffers() {
  m_quadVao.Init();
  m_quadVbo.Init(nullptr, MAX_BATCH_SIZE * 4 * sizeof(QuadVertex));
  m_quadEbo.Init(nullptr, MAX_BATCH_SIZE * 6 * sizeof(GLuint));

  m_quadVao.Bind();
  m_quadVbo.Bind();
  m_quadEbo.Bind();

  m_quadVao.LinkAttrib(m_quadVbo, 0, 2, GL_FLOAT, sizeof(QuadVertex),
                       (void *)offsetof(QuadVertex, position));
  m_quadVao.LinkAttrib(m_quadVbo, 1, 2, GL_FLOAT, sizeof(QuadVertex),
                       (void *)offsetof(QuadVertex, uv));
  m_quadVao.LinkAttrib(m_quadVbo, 2, 4, GL_FLOAT, sizeof(QuadVertex),
                       (void *)offsetof(QuadVertex, color));
  m_quadVao.LinkAttrib(m_quadVbo, 3, 1, GL_FLOAT, sizeof(QuadVertex),
                       (void *)offsetof(QuadVertex, textureIndex));

  m_quadVao.Unbind();
}

void Renderer2D::initCircleShaders() {
  m_circleShader.Compile(circle_vertex_shader, circle_fragment_shader);
  m_circleShader.Activate();
  GLuint projectionLoc =
      glGetUniformLocation(m_circleShader.GetID(), "projection");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, m_projection.value_ptr());
}

void Renderer2D::initCircleBuffers() {
  m_circleVao.Init();
  m_circleVbo.Init(nullptr, MAX_BATCH_SIZE * 4 * sizeof(CircleVertex));
  m_circleEbo.Init(nullptr, MAX_BATCH_SIZE * 6 * sizeof(GLuint));

  m_circleVao.Bind();
  m_circleVbo.Bind();
  m_circleEbo.Bind();

  m_circleVao.LinkAttrib(m_circleVbo, 0, 2, GL_FLOAT, sizeof(CircleVertex),
                         (void *)offsetof(CircleVertex, position));
  m_circleVao.LinkAttrib(m_circleVbo, 1, 2, GL_FLOAT, sizeof(CircleVertex),
                         (void *)offsetof(CircleVertex, uv));
  m_circleVao.LinkAttrib(m_circleVbo, 2, 4, GL_FLOAT, sizeof(CircleVertex),
                         (void *)offsetof(CircleVertex, color));
  m_circleVao.LinkAttrib(m_circleVbo, 3, 2, GL_FLOAT, sizeof(CircleVertex),
                         (void *)offsetof(CircleVertex, center));
  m_circleVao.LinkAttrib(m_circleVbo, 4, 1, GL_FLOAT, sizeof(CircleVertex),
                         (void *)offsetof(CircleVertex, radius));

  m_circleVao.Unbind();
}

void Renderer2D::begin() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  m_quadBatch.vertices.clear();
  m_quadBatch.indices.clear();
  m_quadBatch.textures.clear();
  m_circleBatch.vertices.clear();
  m_circleBatch.indices.clear();
}

void Renderer2D::drawSprite(const Sprite &sprite) {
  if (m_quadBatch.vertices.size() >= MAX_BATCH_SIZE) {
    flushQuad();
  }

  if (!m_quadBatch.filled) {
    flushQuad();
    m_quadBatch.filled = true;
  }

  const Texture *texture = &sprite.getTexture();

  // Find or add texture to batch
  float textureIndex = -1.0f;
  for (size_t i = 0; i < m_quadBatch.textures.size(); ++i) {
    if (m_quadBatch.textures[i] == texture) {
      textureIndex = static_cast<float>(i);
      break;
    }
  }
  if (textureIndex == -1.0f) {
    if (m_quadBatch.textures.size() >= MAX_TEXTURE_SLOTS) {
      flushQuad();
    }
    m_quadBatch.textures.push_back(texture);
    textureIndex = static_cast<float>(m_quadBatch.textures.size() - 1);
  }

  Vec3<float> sPos = sprite.getPosition();

  // Add vertices and indices to batch
  Vec2<float> position = Vec2<float>(sPos.x, sPos.y);
  Vec2<float> size = sprite.getSize();
  Vec4<float> color = sprite.getColor();

  Vec2<float> uv0(0.0f, 1.0f);
  Vec2<float> uv1(1.0f, 1.0f);
  Vec2<float> uv2(1.0f, 0.0f);
  Vec2<float> uv3(0.0f, 0.0f);

  GLuint baseIndex = static_cast<GLuint>(m_quadBatch.vertices.size());

  m_quadBatch.vertices.push_back(
      {{position.x, position.y}, uv0, color, textureIndex});
  m_quadBatch.vertices.push_back(
      {{position.x + size.x, position.y}, uv1, color, textureIndex});
  m_quadBatch.vertices.push_back(
      {{position.x + size.x, position.y + size.y}, uv2, color, textureIndex});
  m_quadBatch.vertices.push_back(
      {{position.x, position.y + size.y}, uv3, color, textureIndex});

  m_quadBatch.indices.insert(m_quadBatch.indices.end(),
                             {baseIndex, baseIndex + 1, baseIndex + 2,
                              baseIndex, baseIndex + 2, baseIndex + 3});
}

void Renderer2D::drawRect(const Rectangle &rectangle) {
  bool filled = rectangle.isFilled();
  if (m_quadBatch.filled != filled) {
    flushQuad();
    m_quadBatch.filled = filled;
  }

  const auto &vertices = rectangle.getVertices();
  const auto &indices =
      rectangle.getIndices(static_cast<GLuint>(m_quadBatch.vertices.size()));

  for (const auto &vertex : vertices) {
    m_quadBatch.vertices.push_back(
        {vertex, {0.0f, 0.0f}, rectangle.getColor(), -1.0f});
  }

  m_quadBatch.indices.insert(m_quadBatch.indices.end(), indices.begin(),
                             indices.end());
}

void Renderer2D::drawCircle(const Circle &circle) {
  bool filled = circle.isFilled();
  if (m_circleBatch.filled != filled) {
    flushCircle();
    m_circleBatch.filled = filled;
  }

  const auto &vertices = circle.getVertices();
  const auto &indices =
      circle.getIndices(static_cast<GLuint>(m_circleBatch.vertices.size()));

  Vec2<float> circleCenter = circle.getPosition();
  float radius = circle.getRadius();

  for (const auto &vertex : vertices) {
    m_circleBatch.vertices.push_back(
        {vertex, {0.0f, 0.0f}, circle.getColor(), circleCenter, radius});
  }

  m_circleBatch.indices.insert(m_circleBatch.indices.end(), indices.begin(),
                               indices.end());
}

void Renderer2D::flushQuad() {
  if (m_quadBatch.vertices.empty())
    return;

  m_quadVao.Bind();
  m_quadVbo.Update(m_quadBatch.vertices.data(),
                   m_quadBatch.vertices.size() * sizeof(QuadVertex));
  m_quadEbo.Update(m_quadBatch.indices.data(),
                   m_quadBatch.indices.size() * sizeof(GLuint));

  m_quadShader.Activate();

  for (size_t i = 0; i < m_quadBatch.textures.size(); ++i) {
    glActiveTexture(GL_TEXTURE0 + i);
    m_quadBatch.textures[i]->Bind();
    m_quadBatch.textures[i]->texUnit(
        m_quadShader, ("textures[" + std::to_string(i) + "]").c_str(), i);
  }

  GLenum drawMode = m_quadBatch.filled ? GL_TRIANGLES : GL_LINES;
  GL_CHECK(glDrawElements(drawMode,
                          static_cast<GLsizei>(m_quadBatch.indices.size()),
                          GL_UNSIGNED_INT, nullptr));

  m_quadVao.Unbind();
  m_quadBatch.vertices.clear();
  m_quadBatch.indices.clear();
  m_quadBatch.textures.clear();
}

void Renderer2D::flushCircle() {
  if (m_circleBatch.vertices.empty())
    return;

  m_circleVao.Bind();
  m_circleVbo.Update(m_circleBatch.vertices.data(),
                     m_circleBatch.vertices.size() * sizeof(CircleVertex));
  m_circleEbo.Update(m_circleBatch.indices.data(),
                     m_circleBatch.indices.size() * sizeof(GLuint));

  m_circleShader.Activate();

  GLenum drawMode = m_circleBatch.filled ? GL_TRIANGLES : GL_LINES;
  GL_CHECK(glDrawElements(drawMode,
                          static_cast<GLsizei>(m_circleBatch.indices.size()),
                          GL_UNSIGNED_INT, nullptr));

  m_circleVao.Unbind();
  m_circleBatch.vertices.clear();
  m_circleBatch.indices.clear();
}

void Renderer2D::end() {
  flushQuad();
  flushCircle();
}

void Renderer2D::shutdown() {
  m_quadShader.Delete();
  m_quadVbo.Delete();
  m_quadEbo.Delete();
  m_quadVao.Delete();

  m_circleShader.Delete();
  m_circleVbo.Delete();
  m_circleEbo.Delete();
  m_circleVao.Delete();
}

void Renderer2D::updateProjection(int windowWidth, int windowHeight) {
  m_windowWidth = windowWidth;
  m_windowHeight = windowHeight;
  m_projection =
      Mat4<float>::ortho(0.0f, static_cast<float>(windowWidth),
                         static_cast<float>(windowHeight), 0.0f, -1.0f, 1.0f);

  m_quadShader.Activate();
  GLuint projectionLoc =
      glGetUniformLocation(m_quadShader.GetID(), "projection");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, m_projection.value_ptr());

  m_circleShader.Activate();
  projectionLoc = glGetUniformLocation(m_circleShader.GetID(), "projection");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, m_projection.value_ptr());
}

void Renderer2D::setDebugMode(bool debug) { m_debugMode = debug; }
