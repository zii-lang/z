#include <Z/IO.hpp>
#include <algorithm>

namespace Z::IO {

MemoryReader::MemoryReader(std::string data)
    : _buffer(std::move(data)), _pos(0) {}

std::size_t MemoryReader::pos() const noexcept { return _pos; }

std::uint8_t MemoryReader::get() noexcept {
  if (_pos >= _buffer.size()) {
    this->setError(InputError::InvalidRead);
    return 0;
  }
  return static_cast<std::uint8_t>(_buffer[_pos++]);
}

std::uint8_t MemoryReader::peek(std::uint32_t offset) noexcept {
  std::size_t idx = _pos + offset;
  if (idx >= _buffer.size()) {
    this->setError(InputError::InvalidPeek);
    return 0;
  }
  return static_cast<std::uint8_t>(_buffer[idx]);
}

bool MemoryReader::eof() const noexcept { return _pos >= _buffer.size(); }

void MemoryReader::seek(std::size_t pos) const noexcept {
  if (pos > _buffer.size()) {
    this->setError(InputError::InvalidSeek);
  }
  const_cast<MemoryReader *>(this)->_pos =
      (pos > _buffer.size() ? _buffer.size() : pos);
}

std::size_t MemoryReader::size() const noexcept { return _buffer.size(); }

std::uint8_t MemoryReader::at(std::size_t index) const noexcept {
  if (index >= _buffer.size()) {
    setError(InputError::InvalidRead);
    return 0;
  }

  return static_cast<std::uint8_t>(_buffer[index]);
}

void MemoryReader::set_name(std::string name) const noexcept {
  this->_name = std::move(name);
}

}; // namespace Z::IO
