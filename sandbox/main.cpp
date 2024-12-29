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
  GameContext::init(640, 480, "Sandbox");

  auto &ctx = GameContext::getInstance();

  Sprite martian("textures/martian.png");
  martian.setPosition(Vec3<float>(100, 100, 1));
  Sprite doomguy("textures/doomguy.png");
  doomguy.setPosition(Vec3<float>(200, 100, 1));

  Circle circle(Vec2<float>(300, 300), 100.0f, false,
                Vec4<float>(0.0f, 1.0f, 0.0f, 1.0f));

  int wWidth = ctx.getWindowWidth();
  int wHeight = ctx.getWindowHeight();
  int wallThickness = 20;

  Rectangle leftWall(Vec2<float>(0, 0),
                     Vec2<float>(wallThickness, wHeight - wallThickness),
                     Vec4<float>(1.0f, 0.0f, 0.0f, 1.0f), false);

  Rectangle rightWall(Vec2<float>(wWidth - wallThickness, wallThickness),
                      Vec2<float>(wallThickness, wHeight),
                      Vec4<float>(1.0f, 1.0f, 0.0f, 1.0f), false);

  Rectangle topWall(Vec2<float>(wallThickness, 0),
                    Vec2<float>(wWidth - wallThickness, wallThickness),
                    Vec4<float>(1.0f, 0.0f, 1.0f, 1.0f), false);

  Rectangle bottomWall(Vec2<float>(0, wHeight - wallThickness),
                       Vec2<float>(wWidth - wallThickness, wallThickness),
                       Vec4<float>(0.0f, 1.0f, 1.0f, 1.0f), false);

  while (!glfwWindowShouldClose(ctx.getWindow())) {
    auto &renderer = ctx.getRenderer();

    renderer.begin();

    renderer.drawCircle(circle);
    renderer.drawRect(leftWall);
    renderer.drawRect(rightWall);
    renderer.drawSprite(doomguy);
    renderer.drawRect(topWall);
    renderer.drawRect(bottomWall);
    renderer.drawSprite(martian);

    renderer.end();

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