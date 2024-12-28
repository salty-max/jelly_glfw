#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <jelly/game_context.h>
#include <jelly/sprite.h>
#include <jelly/rectangle.h>
#include <jelly/circle.h>
#include <jelly/vec.h>

int main() {
  GameContext::init(1280, 720, "Sandbox");

  auto &ctx = GameContext::getInstance();

  Sprite martian("textures/martian.png");
  martian.setPosition(Vec3<float>(100, 100, 1));
  Sprite doomguy("textures/doomguy.png");
  doomguy.setPosition(Vec3<float>(200, 100, 1));
  Rectangle rect(Vec2<float>(20, 20), Vec2<float>(200, 200),
                 Vec4<float>(1.0f, 0.0f, 0.0f, 1.0f));
  Circle circle(Vec2<float>(300, 300), 32, Vec4<float>(0.0f, 1.0f, 0.0f, 1.0f));

  while (!glfwWindowShouldClose(ctx.getWindow())) {
    auto &shapeRenderer = ctx.getShapeRenderer();
    auto &spriteRenderer = ctx.getSpriteRenderer();

    shapeRenderer.begin();

    shapeRenderer.submit(rect);
    shapeRenderer.submit(circle);

    shapeRenderer.end();

    // spriteRenderer.begin();

    // spriteRenderer.submit(martian);
    // spriteRenderer.submit(doomguy);

    // spriteRenderer.end();

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