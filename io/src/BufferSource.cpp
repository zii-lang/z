#include <Z/IO.hpp>

namespace Z {
namespace IO {
BufferSource::BufferSource(LookaheadInputSource &src)
    : _inner(src), _start_pos(src.pos()), _cursor(0) {}

uint8_t BufferSource::peek(uint32_t offset) {
  while (_cursor + offset >= _buffer.size() && !_inner.eof()) {
    _buffer.push_back(_inner.get());
  }
  if (_cursor + offset >= _buffer.size())
    return '\0';
  return _buffer[_cursor + offset];
}
}; // namespace IO
}; // namespace Z
