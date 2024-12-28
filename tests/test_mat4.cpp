#include <iostream>
#include <cassert>
#include <cmath>

#include "jelly/mat.h"
#include "jelly/vec.h"

#define EPSILON 1e-6

bool approxEqual(float a, float b, float epsilon = EPSILON) {
  return std::fabs(a - b) < epsilon;
}

void testIdentity() {
  Mat4<float> identity = Mat4<float>::identity();
  std::cout << "Identity Matrix:\n";
  identity.print();

  // Assert identity matrix values
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      assert(approxEqual(identity.at(i, j), (i == j ? 1.0f : 0.0f)));
    }
  }
  std::cout << "Identity matrix test passed.\n";
}

void testOrtho() {
  float left = 0.0f, right = 1280.0f, bottom = 0.0f, top = 720.0f, near = -1.0f,
        far = 1.0f;
  Mat4<float> ortho = Mat4<float>::ortho(left, right, bottom, top, near, far);

  std::cout << "Orthographic Projection Matrix:\n";
  ortho.print();

  assert(approxEqual(ortho.at(0, 0), 2.0f / (right - left)));
  assert(approxEqual(ortho.at(1, 1), 2.0f / (top - bottom)));
  assert(approxEqual(ortho.at(2, 2), -2.0f / (far - near)));
  assert(approxEqual(ortho.at(3, 0), -(right + left) / (right - left)));
  assert(approxEqual(ortho.at(3, 1), -(top + bottom) / (top - bottom)));
  assert(approxEqual(ortho.at(3, 2), -(far + near) / (far - near)));

  std::cout << "Orthographic projection test passed.\n";
}

void testTranslation() {
  Vec3<float> translation(10.0f, 20.0f, 30.0f);
  Mat4<float> translate = Mat4<float>::translate(translation);
  std::cout << "Translation Matrix:\n";
  translate.print();

  // Check translation values
  assert(approxEqual(translate.at(0, 3), 10.0f));
  assert(approxEqual(translate.at(1, 3), 20.0f));
  assert(approxEqual(translate.at(2, 3), 30.0f));
  std::cout << "Translation test passed.\n";
}

void testScaling() {
  Vec3<float> scale(2.0f, 3.0f, 4.0f);
  Mat4<float> scaling = Mat4<float>::scale(scale);
  std::cout << "Scaling Matrix:\n";
  scaling.print();

  // Check scaling values
  assert(approxEqual(scaling.at(0, 0), 2.0f));
  assert(approxEqual(scaling.at(1, 1), 3.0f));
  assert(approxEqual(scaling.at(2, 2), 4.0f));
  std::cout << "Scaling test passed.\n";
}

void testRotation() {
  // Convert degrees to radians for trigonometric functions
  const float PI = std::atan(1) * 4; // Approximate PI
  const float angle90Rad = PI / 2.0f;

  Mat4<float> rotateX = Mat4<float>::rotateX(angle90Rad);
  std::cout << "Rotation Matrix (X-Axis):\n";
  rotateX.print();

  Mat4<float> rotateY = Mat4<float>::rotateY(angle90Rad);
  std::cout << "Rotation Matrix (Y-Axis):\n";
  rotateY.print();

  Mat4<float> rotateZ = Mat4<float>::rotateZ(angle90Rad);
  std::cout << "Rotation Matrix (Z-Axis):\n";
  rotateZ.print();

  // Check for cosine/sine values, considering floating-point imprecision
  assert(approxEqual(rotateX.at(1, 1), std::cos(angle90Rad)));
  assert(approxEqual(rotateX.at(1, 2), -std::sin(angle90Rad)));
  assert(approxEqual(rotateX.at(2, 1), std::sin(angle90Rad)));
  assert(approxEqual(rotateX.at(2, 2), std::cos(angle90Rad)));

  // Add checks for Y and Z rotations as well
  assert(approxEqual(rotateY.at(0, 0), std::cos(angle90Rad)));
  assert(approxEqual(rotateY.at(0, 2), std::sin(angle90Rad)));
  assert(approxEqual(rotateY.at(2, 0), -std::sin(angle90Rad)));
  assert(approxEqual(rotateY.at(2, 2), std::cos(angle90Rad)));

  assert(approxEqual(rotateZ.at(0, 0), std::cos(angle90Rad)));
  assert(approxEqual(rotateZ.at(0, 1), -std::sin(angle90Rad)));
  assert(approxEqual(rotateZ.at(1, 0), std::sin(angle90Rad)));
  assert(approxEqual(rotateZ.at(1, 1), std::cos(angle90Rad)));

  std::cout << "Rotation tests passed.\n";
}

void testMatrixMultiplication() {
  Mat4<float> translate =
      Mat4<float>::translate(Vec3<float>(10.0f, 20.0f, 30.0f));
  Mat4<float> scale = Mat4<float>::scale(Vec3<float>(2.0f, 2.0f, 2.0f));
  Mat4<float> result = translate * scale;

  std::cout << "Matrix Multiplication Result:\n";
  result.print();

  // Validate specific results
  assert(approxEqual(result.at(0, 3), 10.0f)); // Translation x
  assert(approxEqual(result.at(1, 3), 20.0f)); // Translation y
  assert(approxEqual(result.at(2, 3), 30.0f)); // Translation z
  assert(approxEqual(result.at(0, 0), 2.0f));  // Scaling x
  assert(approxEqual(result.at(1, 1), 2.0f));  // Scaling y
  assert(approxEqual(result.at(2, 2), 2.0f));  // Scaling z
  std::cout << "Matrix multiplication test passed.\n";
}

void testPerspective() {
  // Convert degrees to radians
  const float PI = std::atan(1) * 4; // Approximate PI
  float fovRad = 90.0f * PI / 180.0f;

  Mat4<float> perspective =
      Mat4<float>::perspective(fovRad, 16.0f / 9.0f, 0.1f, 100.0f);
  std::cout << "Perspective Projection Matrix:\n";
  perspective.print();

  // Check key perspective elements, considering floating-point precision
  float tanHalfFov = std::tan(fovRad / 2.0f);
  assert(
      approxEqual(perspective.at(0, 0), 1.0f / ((16.0f / 9.0f) * tanHalfFov)));
  assert(approxEqual(perspective.at(1, 1), 1.0f / tanHalfFov));
  assert(perspective.at(2, 2) <
         0.0f); // Perspective depth value should be negative
  assert(approxEqual(perspective.at(3, 2), -1.0f));
  assert(approxEqual(perspective.at(2, 3),
                     -2.0f * 100.0f * 0.1f / (100.0f - 0.1f)));
  std::cout << "Perspective test passed.\n";
}

int main() {
  testIdentity();
  testOrtho();
  testTranslation();
  testScaling();
  testRotation();
  testMatrixMultiplication();
  testPerspective();

  std::cout << "All tests passed successfully.\n";
  return 0;
}