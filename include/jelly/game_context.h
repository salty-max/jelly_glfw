#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <jelly/renderer.h>

class GameContext {
  GameContext(int windowWidth, int windowHeight, const char *title);
  ~GameContext();

  GLFWwindow *m_window;
  Renderer m_renderer;

  static GameContext *m_instance;

public:
  static void init(int windowWidth, int windowHeight, const char *title);
  static void shutdown();
  static GameContext &getInstance();

  GLFWwindow *getWindow() const;
  Renderer &getRenderer();
};

#endif // GAME_CONTEXT_H
