#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <jelly/game_context.h>
#include <jelly/sprite.h>

int main() {
  GameContext::init(1280, 720, "Sandbox");

  auto &ctx = GameContext::getInstance();

  // Create a sprite
  Sprite psyduck("textures/doomguy.png", 1.0f, 1.0f);

  while (!glfwWindowShouldClose(ctx.getWindow())) {
    ctx.getRenderer().begin();

    psyduck.draw();

    ctx.getRenderer().end();

    glfwSwapBuffers(ctx.getWindow());
    glfwPollEvents();
  }

  GameContext::shutdown();
  return 0;
}