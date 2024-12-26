#ifndef IMAGE_H
#define IMAGE_H

#define STBI_NO_SIMD
#include <stb_image.h>

#include <iostream>

unsigned char *load_image(const char *path, int &width, int &height,
                          int &channels);
void free_image(unsigned char *data);

#endif // IMAGE_H
