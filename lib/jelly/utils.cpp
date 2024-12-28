#include <jelly/utils.h>

template <typename T> T radians(T deg) {
  return deg * static_cast<T>(M_PI) / static_cast<T>(180);
}

template <typename T> T degrees(T rad) {
  return rad * static_cast<T>(180) / static_cast<T>(M_PI);
}

void checkOpenGLError(const char *stmt, const char *file, int line) {
  GLenum err = glGetError();
  while (err != GL_NO_ERROR) {
    std::cerr << "OpenGL error " << err << " at " << file << ":" << line
              << " - for " << stmt << std::endl;
    err = glGetError();
  }
}