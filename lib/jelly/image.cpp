#define STB_IMAGE_IMPLEMENTATION
#include <jelly/image.h>
#include <iostream>

unsigned char *load_image(const char *path, int &width, int &height,
                          int &channels) {
  stbi_set_flip_vertically_on_load(true); // Flip the image for OpenGL

  unsigned char *data = stbi_load(path, &width, &height, &channels, 0);
  if (!data) {
    std::cerr << "stb_image failed to load image: " << path << std::endl;
    std::cerr << "Error: " << stbi_failure_reason() << std::endl;
    return nullptr;
  }

  return data;
}

void free_image(unsigned char *data) { stbi_image_free(data); }