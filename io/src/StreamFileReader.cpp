#include <Z/IO.hpp>

#include <fstream>
#include <iostream>
#include <sstream>

namespace Z::IO {

StreamFileReader::StreamFileReader(const std::string &path) noexcept
    : _in(new std::ifstream(path, std::ios::binary)), _ownsStream(true) {
  this->_name = path;
  auto *fin = static_cast<std::ifstream *>(_in);

  if (!fin->is_open()) {
    setError(InputError::NullInput);
    return;
  }

  _pos = 0;
  _in->clear();
}

StreamFileReader::StreamFileReader(std::istream &stream) noexcept
    : _in(&stream), _ownsStream(false), _pos(0) {}

StreamFileReader::~StreamFileReader() {
  if (_ownsStream) {
    auto *f = dynamic_cast<std::ifstream *>(_in);
    if (f)
      f->close();
    delete _in;
  }
}

size_t StreamFileReader::pos() const noexcept { return _pos; }

uint8_t StreamFileReader::get() noexcept {
  if (!_in) {
    setError(InputError::NullInput);
    return 0;
  }
  int c = _in->get();
  if (_in->eof() || c == EOF) {
    setError(InputError::EOFReached);
    return 0;
  }
  ++_pos;
  return static_cast<uint8_t>(c);
}

uint8_t StreamFileReader::peek(uint32_t n) noexcept {
  if (!_in) {
    setError(InputError::NullInput);
    return 0;
  }

  // Save current position
  std::istream::pos_type cur = _in->tellg();
  if (cur == -1) {
    setError(InputError::InvalidSeek);
    return 0;
  }

  // Advance n positions
  _in->seekg(n, std::ios::cur);
  int c = _in->peek();

  if (c == EOF || _in->eof()) {
    setError(InputError::EOFReached);
    _in->clear();
    _in->seekg(cur);
    return 0;
  }

  _in->clear();
  _in->seekg(cur);
  return static_cast<uint8_t>(c);
}

bool StreamFileReader::eof() const noexcept {
  if (!_in) {
    return true; // no stream -> definitely at EOF
  }

  // If stream not open or in error, treat as EOF
  const std::ifstream *fin = dynamic_cast<const std::ifstream *>(_in);
  if (fin && !fin->is_open()) {
    return true;
  }

  // If stream reached EOF or failed, report as EOF
  if (_in->eof() || _in->fail()) {
    return true;
  }

  // Attempt to peek one character ahead without consuming
  std::istream::pos_type current = _in->tellg();
  if (current == -1) {
    return true; // invalid position, stream likely closed
  }

  int next = _in->peek();
  _in->clear(); // reset peek side effects

  return next == EOF;
}

std::unique_ptr<RandomAccessReader>
StreamFileReader::toRandomAccess() noexcept {
  if (!_in)
    return nullptr;

  // Read the remaining stream into memory
  std::ostringstream oss;
  oss << _in->rdbuf();
  std::string data = oss.str();

  return std::make_unique<MemoryReader>(std::move(data));
}

void StreamFileReader::set_name(std::string name) const noexcept {
  this->_name = std::move(name);
}

}; // namespace Z::IO
