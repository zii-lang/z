#include <Z/Syntax/FileSource>

namespace Z {
namespace Syntax {

FileSource::FileSource(const std::string &filepath)
    : in(filepath, std::ios::binary), path(filepath) {
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

uint32_t FileSource::peek(uint32_t n) {
  if ((static_cast<uint32_t>(in.tellg()) + 0) < file_size) {
    in.seekg(n, std::ios::cur);
    const uint32_t ch = in.peek();
    in.seekg(-static_cast<int32_t>(n), std::ios::cur);
    return ch;
  } else {
    return '\0';
  }
}

uint32_t FileSource::get() {
  this->inc_column();
  return eof() ? '\0' : static_cast<uint32_t>(in.get());
}

bool FileSource::eof() { return in.peek() == EOF; }

uint32_t FileSource::get_pos() {
  auto pos = in.tellg();
  return (pos == -1) ? static_cast<uint32_t>(file_size)
                     : static_cast<uint32_t>(pos);
}

void FileSource::set_pos(uint32_t pos) { in.seekg(pos, std::ios::beg); }

const std::string FileSource::get_path() { return this->path; }

const std::string FileSource::slice(uint32_t start, uint32_t length) {
  in.seekg(0, std::ios::end);
  size_t file_size = in.tellg();
  if (start >= file_size)
    return {};

  in.seekg(start, std::ios::beg);
  std::string buffer(std::min<uint32_t>(length, file_size - start), '\0');
  in.read(buffer.data(), buffer.size());
  buffer.resize(in.gcount());
  return buffer;
}

}; // namespace Syntax
}; // namespace Z
