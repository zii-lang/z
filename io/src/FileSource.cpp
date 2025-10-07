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

size_t FileSource::pos() const {
  if (this->eof()) {
    return this->_size;
  }
  return static_cast<size_t>(this->_in.tellg());
}

uint8_t FileSource::get() const { return eof() ? '\0' : this->_in.get(); }

bool FileSource::eof() const {
  this->_in.peek();
  return this->_in.eof();
}

uint8_t FileSource::peek(size_t offset) {
  if (offset == 0) {
    if (eof()) {
      return '\0';
    }
    return this->_in.peek();
  }

  if ((static_cast<size_t>(this->_in.tellg()) + offset) < this->_size) {
    this->_in.seekg(offset, std::ios::cur);
    const uint8_t ch = this->_in.peek();
    this->_in.clear();
    this->_in.seekg(-offset, std::ios::cur);
    return ch;
  } else {
    return '\0';
  }
}

void FileSource::seek(size_t offset) const {
  this->_in.seekg(offset, std::ios::cur);
  if (offset < 0 && eof()) {
    this->_in.clear();
  }
  this->_in.peek(); // to set eof flag again.
}

void FileSource::seekTo(size_t offset) const {
  if (eof()) {
    this->_in.clear();
  }
  this->_in.seekg(offset, std::ios::beg);
  this->_in.peek(); // to set eof flag again.
}

uint32_t FileSource::size() const { return this->_size; }

}; // namespace IO
}; // namespace Z
