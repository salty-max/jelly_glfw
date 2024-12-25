#include <iostream>
#include <math.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <jelly/io.h>
#include <jelly/shader.h>
#include <jelly/vao.h>
#include <jelly/vbo.h>
#include <jelly/ebo.h>

int main() {
  glfwInit();

  GLfloat vertices[] = {
      -0.5f,     -0.5f * float(sqrt(3)) / 3,    0.0f, // Lower left corner
      0.5f,      -0.5f * float(sqrt(3)) / 3,    0.0f, // Lower right corner
      0.0f,      0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
      -0.5f / 2, 0.5f * float(sqrt(3)) / 6,     0.0f, // Inner left
      0.5f / 2,  0.5f * float(sqrt(3)) / 6,     0.0f, // Inner right
      0.0f,      -0.5f * float(sqrt(3)) / 3,    0.0f  // Inner down

  };

  GLuint indices[] = {
      0, 3, 5, // Lower left triangle
      3, 2, 4, // Lower right triangle
      5, 4, 1  // Upper triangle
  };

  int windowWidth = 800;
  int windowHeight = 800;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
      glfwCreateWindow(windowWidth, windowHeight, "Jelly", nullptr, nullptr);

  if (window == nullptr) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (gladLoadGL((GLADloadfunc)glfwGetProcAddress) == 0) {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    glfwDestroyWindow(window);
    glfwTerminate();
    return -1;
  }

  glViewport(0, 0, windowWidth, windowHeight);

  Shader shaderProgram;

  VAO VAO;
  VAO.Bind();

  VBO VBO(vertices, sizeof(vertices));
  EBO EBO(indices, sizeof(indices));

  VAO.LinkVBO(VBO, 0);

  VAO.Unbind();
  VBO.Unbind();
  EBO.Unbind();

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.Activate();
    VAO.Bind();
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  VAO.Delete();
  VBO.Delete();
  EBO.Delete();
  shaderProgram.Delete();

  glfwDestroyWindow(window);

  glfwTerminate();

  return 0;
}