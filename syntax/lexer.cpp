#include "lexer.h"

namespace Z {
namespace Syntax {
/**
 * ------------------------------------------
 * StringSource Code
 * ------------------------------------------
 */
StringSource::StringSource(const std::string &str) : data(str) {}
uint32_t StringSource::peek() {
  return index < data.size() ? data[index] : '\0';
}

uint32_t StringSource::get() {
  return index < data.size() ? data[index++] : '\0';
}

bool StringSource::eof() { return index >= data.size(); }

size_t StringSource::position() { return index; }

/**
 * ------------------------------------------
 *  FileSource
 * ------------------------------------------
 */
FileSource::FileSource(const std::string &filepath)
    : in(filepath, std::ios::binary) {
  if (!in.is_open()) {
    throw std::runtime_error("Cannot open file: " + filepath);
  }
  in.seekg(0, std::ios::end);
  file_size = in.tellg();
  in.seekg(0, std::ios::beg);
}

uint32_t FileSource::peek() {
  return eof() ? '\0' : static_cast<uint32_t>(in.peek());
}

uint32_t FileSource::get() {
  return eof() ? '\0' : static_cast<uint32_t>(in.get());
}

bool FileSource::eof() { return in.peek() == EOF; }

size_t FileSource::position() {
  auto pos = in.tellg();
  return (pos == -1) ? static_cast<size_t>(file_size)
                     : static_cast<size_t>(pos);
}

} // namespace Syntax
} // namespace Z
