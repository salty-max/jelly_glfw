/**
 * @file io.h
 * @brief Provides functions for reading from and writing to files.
 */
#ifndef IO_H
#define IO_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

/**
 * @brief Reads the contents of a file.
 *
 * This function opens the file at the specified path, reads its contents,
 * and returns them as a null-terminated string. The caller is responsible
 * for freeing the returned string.
 *
 * @param path The path to the file to be read.
 * @return A pointer to a null-terminated string containing the file contents,
 *         or NULL if the file could not be read.
 */
std::string read_file(const char *path);

/**
 * @brief Writes data to a file.
 *
 * This function opens the file at the specified path and writes the provided
 * data to it. If the file already exists, its contents will be overwritten.
 *
 * @param path The path to the file to be written.
 * @param data The null-terminated string to be written to the file.
 */
void write_file(const char *path, const char *data);

#endif // IO_H