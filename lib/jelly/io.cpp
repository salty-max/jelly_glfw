#include "jelly/io.h"

std::string read_file(const char *path) {
  try {
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
      std::cerr << "Error: Unable to open file for reading: " << path
                << std::endl;
      return "";
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
  } catch (const std::exception &e) {
    std::cerr << "Error: Exception while reading file: " << e.what()
              << std::endl;
    return "";
  }
}

void write_file(const char *path, const char *data) {
  try {
    std::ofstream file(path, std::ios::out | std::ios::binary);
    if (!file.is_open()) {
      std::cerr << "Error: Unable to open file for writing: " << path
                << std::endl;
      return;
    }

    file.write(data, std::strlen(data));

    if (!file) {
      std::cerr << "Error: Failed to write data to file: " << path << std::endl;
    }
  } catch (const std::exception &e) {
    std::cerr << "Error: Exception while writing file: " << e.what()
              << std::endl;
  }
}
