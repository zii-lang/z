#include <fstream>
#include <ios>
#include <iostream>

#include <Z/IO.hpp>

namespace Z {
namespace IO {

FileSource::FileSource(const std::string &filepath)
    : _in(filepath, std::ios::binary) {
  if (!this->_in.is_open()) {
    throw std::runtime_error("Cannot open file: " + filepath);
  }
  this->_in.seekg(0, std::ios::end);
  this->_size = this->_in.tellg();
  this->_in.clear();
  this->_in.seekg(0, std::ios::beg);
}

uint32_t FileSource::peek(uint32_t n) {
  if (n == 0) {
    return this->_in.peek();
  }
  if ((static_cast<uint32_t>(this->_in.tellg()) + n) < this->_size) {
    this->_in.seekg(n, std::ios::cur);
    const uint32_t ch = this->_in.peek();
    this->clear();
    this->_in.seekg(-static_cast<int32_t>(n), std::ios::cur);
    return ch;
  } else {
    return '\0';
  }
}

uint32_t FileSource::get() {
  if (eof()) {
    return '\0';
  }
  uint32_t ch = static_cast<uint32_t>(this->_in.get());
  return ch;
}

bool FileSource::eof() { return _in.eof(); }

size_t FileSource::pos() const {
  const size_t p = this->_in.tellg();
  if (p == std::streampos(-1))
    return 0;
  return static_cast<size_t>(p);
}

void FileSource::seek(size_t pos, SeekKind kind) {
  switch (kind) {
  case SeekKind::Start:
    this->_in.seekg(pos, std::ios::beg);
    break;
  case SeekKind::Current:
    this->_in.seekg(pos, std::ios::cur);
    break;
  case SeekKind::End:
    this->_in.seekg(pos, std::ios::end);
    break;
  }
}

uint32_t FileSource::size() const { return this->_size; }

std::string FileSource::slice(size_t start, size_t length) const {
  this->clear();
  this->_in.seekg(static_cast<std::streamoff>(start), std::ios::beg);

  std::string result(length, '\0');
  this->_in.read(result.data(), static_cast<std::streamsize>(length));
  result.resize(static_cast<size_t>(_in.gcount()));
  return result;
}

void FileSource::clear() const { this->_in.clear(); }

}; // namespace IO
}; // namespace Z
