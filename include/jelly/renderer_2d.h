#ifndef RENDERER_2D_H
#define RENDERER_2D_H

#include <vector>

#include <glad/gl.h>

#include <jelly/sprite.h>
#include <jelly/rectangle.h>
#include <jelly/circle.h>
#include <jelly/mat.h>
#include <jelly/vec.h>
#include <jelly/vao.h>
#include <jelly/vbo.h>
#include <jelly/ebo.h>
#include <jelly/texture.h>
#include <jelly/shader.h>
#include <jelly/utils.h>

const size_t MAX_BATCH_SIZE = 10000;
const size_t MAX_TEXTURE_SLOTS = 32;

struct QuadVertex {
  Vec2<float> position;
  Vec2<float> uv;
  Vec4<float> color;
  float textureIndex;
};

struct CircleVertex {
  Vec2<float> position;
  Vec2<float> uv;
  Vec4<float> color;
  Vec2<float> center;
  float radius;
};

class Renderer2D {
  struct QuadBatch {
    std::vector<QuadVertex> vertices;
    std::vector<GLuint> indices;
    std::vector<const Texture *> textures;
    bool filled = true;
  };

  struct CircleBatch {
    std::vector<CircleVertex> vertices;
    std::vector<GLuint> indices;
    bool filled = true;
  };

  int m_windowWidth;
  int m_windowHeight;
  float m_scale;
  bool m_debugMode;

  Shader m_quadShader;
  VAO m_quadVao;
  VBO m_quadVbo;
  EBO m_quadEbo;
  QuadBatch m_quadBatch;

  Shader m_circleShader;
  VAO m_circleVao;
  VBO m_circleVbo;
  EBO m_circleEbo;
  CircleBatch m_circleBatch;

  Mat4<float> m_projection;

  void initQuadShaders();
  void initCircleShaders();

  void initQuadBuffers();
  void initCircleBuffers();

  void flushQuad();
  void flushCircle();

public:
  Renderer2D(int windowWidth, int windowHeight, float scale);
  ~Renderer2D();

  void init();
  void begin();
  void updateProjection(int windowWidth, int windowHeight);
  void drawSprite(const Sprite &sprite);
  void drawRect(const Rectangle &rectangle);
  void drawCircle(const Circle &circle);
  void end();
  void shutdown();
  void setDebugMode(bool debug);
};

#endif // RENDERER_2D_H