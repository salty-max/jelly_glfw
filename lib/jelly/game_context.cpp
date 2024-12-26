#include <jelly/game_context.h>

GameContext *GameContext::m_instance = nullptr;

void GameContext::init(int windowWidth, int windowHeight, const char *title) {
  std::cout << "\033[34mJelly Engine v0.1\033[0m" << std::endl;

  if (m_instance == nullptr) {
    m_instance = new GameContext(windowWidth, windowHeight, title);
  }
}

void GameContext::shutdown() {
  if (m_instance != nullptr) {
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

GameContext::GameContext(int windowWidth, int windowHeight, const char *title)
    : m_renderer(windowWidth, windowHeight) {
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    std::terminate();
  }

  std::cout << "Using GLFW version " << glfwGetVersionString() << std::endl;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

  glViewport(0, 0, windowWidth, windowHeight);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  m_renderer.init_shaders();

  std::cout << "Open GL loaded succesfully" << std::endl;
  std::cout << "\t Version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "\t Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "\t Renderer: " << glGetString(GL_RENDERER) << std::endl;
}

GameContext::~GameContext() {
  glfwDestroyWindow(m_window);
  glfwTerminate();
}

GLFWwindow *GameContext::getWindow() const { return m_window; }

Renderer &GameContext::getRenderer() { return m_renderer; }