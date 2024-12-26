#include "jelly/debug_overlay.h"

void DebugOverlay::init(GLFWwindow *window) {
  m_window = window;

  // Initialize ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable keyboard navigation

  // Initialize ImGui backends
  ImGui_ImplGlfw_InitForOpenGL(m_window, true);
  ImGui_ImplOpenGL3_Init("#version 330");
}

void DebugOverlay::beginFrame() {
  // Start a new ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void DebugOverlay::render() {
  int fbWidth, fbHeight;
  glfwGetFramebufferSize(m_window, &fbWidth, &fbHeight);

  // Retrieve the current viewport size
  ImGuiIO &io = ImGui::GetIO();
  io.DisplaySize =
      ImVec2(static_cast<float>(fbWidth), static_cast<float>(fbHeight));

  float windowWidth = io.DisplaySize.x;
  float windowHeight = io.DisplaySize.y;

  // Set the next window's position and size
  ImGui::SetNextWindowPos(ImVec2(windowWidth * 0.75f, 0),
                          ImGuiCond_Always); // Right side
  ImGui::SetNextWindowSize(ImVec2(windowWidth * 0.25f, windowHeight),
                           ImGuiCond_Always); // Takes up 25% width, full height

  // Example debug window
  ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_NoResize);

  ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
  ImGui::Text("Window Size: %d x %d", windowWidth, windowHeight);

  ImGui::End();

  // Render the ImGui frame
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void DebugOverlay::shutdown() {
  // Clean up ImGui resources
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}
