#include <Z/IO.hpp>
#include <cstdio>
#include <stdexcept>

namespace Z::IO {

ForwardFileSource::ForwardFileSource(const std::string &path)
    : _in(new std::ifstream(path, std::ios::in)), _ownsStream(true) {
  if (!_in || _in->bad()) {
    delete _in;
    throw std::runtime_error("Failed to open file: " + path);
  }
}

ForwardFileSource::ForwardFileSource(std::istream &stream)
    : _in(&stream), _ownsStream(false) {
  if (!_in || _in->bad())
    throw std::runtime_error("Bad stream given.");
}

ForwardFileSource::~ForwardFileSource() {
  if (_ownsStream)
    delete _in;
}

size_t ForwardFileSource::pos() const { return _pos; }

uint8_t ForwardFileSource::get() {
  int c = _in->get();
  if (c == EOF) {
    // Refresh file on EOF to make sure we reached actual EOF and no more data
    // is coming.
    if (eof()) {
      throw std::runtime_error("ForwardFileSource: EOF reached");
    } else {
      c = _in->get();
    }
  }
  ++_pos;
  return static_cast<uint8_t>(c);
}

uint8_t ForwardFileSource::peek(uint32_t n) {
  std::streampos orig = _in->tellg();
  if (orig == -1)
    throw std::runtime_error("ForwardFileSource: invalid stream position");

  for (uint32_t i = 0; i < n; ++i)
    _in->get();
  int c = _in->get();

  _in->clear();     // clear EOF if reached
  _in->seekg(orig); // restore position

  return static_cast<uint8_t>(c);
}

bool ForwardFileSource::eof() const {
  auto *in = const_cast<std::istream *>(_in);
  in->peek();
  if (in->eof()) {
    in->clear();                 // clear flags
    in->seekg(0, std::ios::cur); // refresh internal buffer
    in->peek();                  // set eofbit if still EOF
  }
  return in->eof();
}

} // namespace Z::IO
