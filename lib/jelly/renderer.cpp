#include <jelly/renderer.h>

Renderer::Renderer(int windowWidth, int windowHeight)
    : m_windowWidth(windowWidth), m_windowHeight(windowHeight) {}

void Renderer::init_shaders() {
  m_defaultShader = std::make_unique<Shader>();
  m_defaultShader->Activate();

  m_projectionMatrix =
      Mat4<float>::ortho(-static_cast<float>(m_windowWidth) / m_windowHeight,
                         static_cast<float>(m_windowWidth) / m_windowHeight,
                         -1.0f, 1.0f, -1.0f, 1.0f);

  GLuint projLoc = glGetUniformLocation(m_defaultShader->GetID(), "projection");
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, &m_projectionMatrix.data[0][0]);

  GLuint scaleLoc = glGetUniformLocation(m_defaultShader->GetID(), "scale");
  glUniform1f(scaleLoc, 0.0f);
}

void Renderer::begin() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Clear the screen to black
  glClear(GL_COLOR_BUFFER_BIT);
  // Activate default shader for this frame
  m_defaultShader->Activate();
}

void Renderer::end() {
  // Perform any end-of-frame operations if needed
  // For now, this is empty but reserved for potential post-processing or debug
  // rendering
}

void Renderer::updateProjection(int windowWidth, int windowHeight) {
  m_projectionMatrix = Mat4<float>::ortho(
      -static_cast<float>(windowWidth) / windowHeight,
      static_cast<float>(windowWidth) / windowHeight, -1.0f, 1.0f, -1.0f, 1.0f);
  GLuint projLoc = glGetUniformLocation(m_defaultShader->GetID(), "projection");
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, &m_projectionMatrix.data[0][0]);
}

Shader &Renderer::getDefaultShader() { return *m_defaultShader; }

void Renderer::cleanup() { m_defaultShader->Delete(); }
