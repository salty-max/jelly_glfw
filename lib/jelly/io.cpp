#include "jelly/io.h"

const char *read_file(const char *path) {
  try {
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
      std::cerr << "Error: Unable to open file for reading: " << path
                << std::endl;
      return nullptr;
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    // Dynamically allocate memory for the content
    char *result = new char[content.size() + 1];
    std::copy(content.begin(), content.end(), result);
    result[content.size()] = '\0';
    std::cout << "Data read from file: " << result << std::endl;
    return result;
  } catch (const std::exception &e) {
    std::cerr << "Error: Exception while reading file: " << e.what()
              << std::endl;
    return nullptr;
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
