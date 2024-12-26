#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <jelly/game_context.h>
#include <jelly/sprite.h>

int main() {
  GameContext::init(1280, 720, "Sandbox", true);

  auto &ctx = GameContext::getInstance();

  // Create a sprite
  Sprite psyduck("textures/psyduck.png", 1.0f, 1.0f);

  while (!glfwWindowShouldClose(ctx.getWindow())) {

    ctx.getRenderer().begin();

    psyduck.draw();

    ctx.getRenderer().end();

    if (ctx.isDebugOverlayEnabled()) {
      ctx.getDebugOverlay().beginFrame();
      ctx.getDebugOverlay().render();
    }

    glfwSwapBuffers(ctx.getWindow());
    glfwPollEvents();
  }

  GameContext::shutdown();
  return 0;
}