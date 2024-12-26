#include <jelly/sprite.h>
#include <jelly/game_context.h>

Sprite::Sprite(const char *texturePath, float width, float height)
    : m_texture(texturePath, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA,
                GL_UNSIGNED_BYTE),
      m_vbo(nullptr, 0), m_ebo(nullptr, 0) {
  // Vertex data
  GLfloat vertices[32] = {
      // Position         // Color          // Texture coordinates
      -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // Lower left
      -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // Upper left
      0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // Upper right
      0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f  // Lower right
  };

  // Indices
  GLuint indices[] = {
      0, 1, 2, // Upper left triangle
      2, 3, 0  // Lower right triangle
  };

  // Set up VAO, VBO, and EBO
  m_vao.Bind();
  m_vbo = VBO(vertices, sizeof(vertices));
  m_ebo = EBO(indices, sizeof(indices));

  m_vao.LinkAttrib(m_vbo, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void *)0);
  m_vao.LinkAttrib(m_vbo, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat),
                   (void *)(3 * sizeof(GLfloat)));
  m_vao.LinkAttrib(m_vbo, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat),
                   (void *)(6 * sizeof(GLfloat)));

  m_vao.Unbind();
  m_vbo.Unbind();
  m_ebo.Unbind();

  // Set texture uniform
  m_texture.texUnit(GameContext::getInstance().getRenderer().getDefaultShader(),
                    "tex0", 0);
}

Sprite::~Sprite() {
  m_vao.Delete();
  m_vbo.Delete();
  m_ebo.Delete();
  m_texture.Delete();
}

void Sprite::draw() const {
  auto &renderer = GameContext::getInstance().getRenderer();
  const Shader &shader = renderer.getDefaultShader();

  shader.Activate();
  m_texture.Bind();
  m_vao.Bind();

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
