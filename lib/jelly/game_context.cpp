#include <jelly/game_context.h>

GameContext *GameContext::m_instance = nullptr;

void GameContext::init(int windowWidth, int windowHeight, const char *title,
                       bool debugOverlayEnabled) {
  std::cout << "\033[34mJelly Engine v0.1\033[0m" << std::endl;

  if (m_instance == nullptr) {
    m_instance =
        new GameContext(windowWidth, windowHeight, title, debugOverlayEnabled);
  }

  if (debugOverlayEnabled) {
    m_instance->m_debugOverlay.init(m_instance->getWindow());
  }
}

void GameContext::shutdown() {

  if (m_instance != nullptr) {
    if (m_instance->isDebugOverlayEnabled()) {
      m_instance->m_debugOverlay.shutdown();
    }

    m_instance->m_spriteRenderer.shutdown();
    m_instance->m_shapeRenderer.shutdown();

    delete m_instance;
    m_instance = nullptr;
  }
}

GameContext &GameContext::getInstance() {
  if (m_instance == nullptr) {
    std::cerr << "GameContext not initialized! Call Jelly::init() first."
              << std::endl;
    std::terminate();
  }
  return *m_instance;
}

GameContext::GameContext(int windowWidth, int windowHeight, const char *title,
                         bool debugOverlayEnabled)
    : m_spriteRenderer(windowWidth, windowHeight, 1.0f),
      m_shapeRenderer(windowWidth, windowHeight, 1.0f),
      m_debugOverlayEnabled(debugOverlayEnabled) {
  std::cout << "Initializing GLFW..." << std::endl;

  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    std::terminate();
  }

  std::cout << "Using GLFW version " << glfwGetVersionString() << std::endl;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window =
      glfwCreateWindow(windowWidth, windowHeight, title, nullptr, nullptr);
  if (m_window == nullptr) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    std::terminate();
  }

  // Center window
  glfwSetWindowPos(m_window, 2160 / 2 - windowWidth / 2,
                   1440 / 2 - windowHeight / 2);

  glfwMakeContextCurrent(m_window);
  if (gladLoadGL((GLADloadfunc)glfwGetProcAddress) == 0) {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    glfwDestroyWindow(m_window);
    glfwTerminate();
    std::terminate();
  }

  int width, height;
  glfwGetFramebufferSize(m_window, &width, &height);
  glViewport(0, 0, width, height);

  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(
      [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
         const GLchar *message, const void *userParam) {
        std::cerr << "GL Debug: " << message << std::endl;
      },
      nullptr);

  std::cout << "Open GL loaded succesfully" << std::endl;
  std::cout << "\t Version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "\t Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "\t Renderer: " << glGetString(GL_RENDERER) << std::endl;

  m_spriteRenderer.init();
  m_shapeRenderer.init();
}

GameContext::~GameContext() {
  glfwDestroyWindow(m_window);
  glfwTerminate();
}

GLFWwindow *GameContext::getWindow() const { return m_window; }

int GameContext::getWindowWidth() const {
  int width, height;
  glfwGetWindowSize(m_window, &width, &height);
  return width;
}

int GameContext::getWindowHeight() const {
  int width, height;
  glfwGetWindowSize(m_window, &width, &height);
  return height;
}

SpriteRenderer &GameContext::getSpriteRenderer() { return m_spriteRenderer; }

ShapeRenderer &GameContext::getShapeRenderer() { return m_shapeRenderer; }

DebugOverlay &GameContext::getDebugOverlay() { return m_debugOverlay; }

bool GameContext::isDebugOverlayEnabled() const {
  return m_debugOverlayEnabled;
}