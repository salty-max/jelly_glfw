/**
 * @file utils.h
 * @brief This file contains utility functions.
 */
#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// #ifdef DEBUG
#define GL_CHECK(stmt)                                                         \
  do {                                                                         \
    stmt;                                                                      \
    checkOpenGLError(#stmt, __FILE__, __LINE__);                               \
  } while (0)
// #else
// #define GL_CHECK(stmt) stmt
// #endif

/**
 * @brief Converts degrees to radians.
 *
 * @param deg The input value in degrees.
 * @tparam T The type of the input value.
 */
template <typename T = float> T radians(T deg);

/**
 * @brief Converts radians to degrees.
 *
 * @param rad The input value in radians.
 * @tparam T The type of the input value.
 */
template <typename T = float> T degrees(T rad);

void checkOpenGLError(const char *stmt, const char *file, int line);

#endif // UTILS_H