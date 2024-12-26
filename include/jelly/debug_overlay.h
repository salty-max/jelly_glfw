#ifndef DEBUG_OVERLAY_H
#define DEBUG_OVERLAY_H

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

/**
 * @brief A class to manage the debug overlay using Dear ImGui.
 */
class DebugOverlay {
  GLFWwindow *m_window;

public:
  /**
   * @brief Initializes the debug overlay.
   * @param window The GLFW window to bind the overlay to.
   */
  void init(GLFWwindow *window);

  /**
   * @brief Starts a new frame for the debug overlay.
   */
  void beginFrame();

  /**
   * @brief Renders the debug overlay.
   */
  void render();

  /**
   * @brief Shuts down the debug overlay and cleans up resources.
   */
  void shutdown();
};

#endif // DEBUG_OVERLAY_H
