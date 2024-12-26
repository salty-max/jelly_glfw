#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <jelly/renderer.h>
#include <jelly/debug_overlay.h>

class GameContext {
  GameContext(int windowWidth, int windowHeight, const char *title,
              bool debugOverlayEnabled);
  ~GameContext();

  GLFWwindow *m_window;
  Renderer m_renderer;
  DebugOverlay m_debugOverlay;

  bool m_debugOverlayEnabled;

  static GameContext *m_instance;

public:
  static void init(int windowWidth, int windowHeight, const char *title,
                   bool debugOverlayEnabled = false);
  static void shutdown();
  static GameContext &getInstance();

  GLFWwindow *getWindow() const;
  Renderer &getRenderer();
  DebugOverlay &getDebugOverlay();
  bool isDebugOverlayEnabled() const;
};

#endif // GAME_CONTEXT_H
