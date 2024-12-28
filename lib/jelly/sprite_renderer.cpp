#include <jelly/sprite_renderer.h>

SpriteRenderer::SpriteRenderer(int windowWidth, int windowHeight, float scale)
    : m_windowWidth(windowWidth), m_windowHeight(windowHeight), m_scale(scale),
      m_projection(Mat4<float>::ortho(0.0f, static_cast<float>(windowWidth),
                                      static_cast<float>(windowHeight), 0.0f,
                                      -1.0f, 1.0f)) {}

SpriteRenderer::~SpriteRenderer() {}

void SpriteRenderer::initShaders() {
  std::cout << "Initializing sprite shaders..." << std::endl;

  m_spriteShader.Compile(batch_quad_vertex_shader, batch_quad_fragment_shader);

  m_spriteShader.Activate();
  GLuint projectionLoc =
      glGetUniformLocation(m_spriteShader.GetID(), "projection");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, m_projection.value_ptr());

  std::cout << "Sprite shaders initialized." << std::endl;
}

void SpriteRenderer::initBuffers() {
  m_vao.Init();
  m_vbo.Init(nullptr, MAX_SPRITE_BATCH_SIZE * 4 * sizeof(SpriteVertex));
  m_ebo.Init(nullptr, MAX_SPRITE_BATCH_SIZE * 6 * sizeof(GLuint));

  m_vao.Bind();
  m_vbo.Bind();
  m_ebo.Bind();

  m_vao.LinkAttrib(m_vbo, 0, 2, GL_FLOAT, sizeof(SpriteVertex),
                   (void *)offsetof(SpriteVertex, position));
  m_vao.LinkAttrib(m_vbo, 1, 2, GL_FLOAT, sizeof(SpriteVertex),
                   (void *)offsetof(SpriteVertex, uvs));
  m_vao.LinkAttrib(m_vbo, 2, 4, GL_FLOAT, sizeof(SpriteVertex),
                   (void *)offsetof(SpriteVertex, color));

  m_vao.Unbind();
}

void SpriteRenderer::init() {
  initShaders();
  initBuffers();
}

void SpriteRenderer::begin() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  m_currentBatch.clear();
  m_indices.clear();
}

void SpriteRenderer::submit(const Sprite &sprite) {
  if (m_currentBatch.size() / 4 >= MAX_SPRITE_BATCH_SIZE) {
    flush();
  }

  const Texture *spriteTexture = &sprite.getTexture();

  if (m_currentTexture && m_currentTexture != spriteTexture) {
    flush();
  }

  m_currentTexture = spriteTexture;

  Vec3<float> spritePosition = sprite.getPosition();

  // Get sprite properties
  Vec2<float> position = Vec2<float>(spritePosition.x, spritePosition.y);
  Vec2<float> size = sprite.getSize();
  Vec4<float> color = sprite.getColor();
  Vec2<float> uv0(0.0f, 1.0f); // Top-left
  Vec2<float> uv1(1.0f, 1.0f); // Top-right
  Vec2<float> uv2(1.0f, 0.0f); // Bottom-right
  Vec2<float> uv3(0.0f, 0.0f); // Bottom-left

  GLuint baseIndex = static_cast<GLuint>(m_currentBatch.size());

  m_currentBatch.push_back(
      {Vec2<float>(position.x, position.y), uv0, color}); // Bottom-left
  m_currentBatch.push_back({Vec2<float>(position.x + size.x, position.y), uv1,
                            color}); // Bottom-right
  m_currentBatch.push_back(
      {Vec2<float>(position.x + size.x, position.y + size.y), uv2,
       color}); // Top-right
  m_currentBatch.push_back(
      {Vec2<float>(position.x, position.y + size.y), uv3, color}); // Top-left

  // Add indices for this sprite
  m_indices.insert(m_indices.end(), {baseIndex, baseIndex + 1, baseIndex + 2,
                                     baseIndex, baseIndex + 2, baseIndex + 3});
}

void SpriteRenderer::flush() {
  if (m_currentBatch.empty())
    return;

  m_vao.Bind();
  m_vbo.Update(m_currentBatch.data(),
               m_currentBatch.size() * sizeof(SpriteVertex));
  m_ebo.Update(m_indices.data(), m_indices.size() * sizeof(GLuint));

  m_spriteShader.Activate();

  // Texture activation and binding
  glActiveTexture(GL_TEXTURE0);
  m_currentTexture->Bind();
  m_currentTexture->texUnit(m_spriteShader, "texture_slot", 0);

  GLint vao, vbo, ebo;
  glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vao);
  glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &vbo);
  glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &ebo);

  glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()),
                 GL_UNSIGNED_INT, 0);

  m_vao.Unbind();

  m_currentBatch.clear();
  m_indices.clear();
}

void SpriteRenderer::end() { flush(); }

void SpriteRenderer::shutdown() {
  m_spriteShader.Delete();
  m_vbo.Delete();
  m_ebo.Delete();
  m_vao.Delete();
}