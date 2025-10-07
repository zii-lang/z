#ifndef Z_IO_INPUT_SOURCE_HPP
#define Z_IO_INPUT_SOURCE_HPP

#include <cstddef>
#include <cstdint>

namespace Z {
namespace IO {

/**
 * Interface class for reading a buffer, lexer accept classes that implement
 * this class.
 */
class InputSource {
public:
  virtual ~InputSource() = default;
  virtual size_t pos() const = 0;
  virtual uint8_t get() = 0;
  virtual bool eof() const = 0;
};

/**
 * Forward only, Lookahead source stream.
 */
class LookaheadInputSource : public InputSource {
public:
  // Deconstructor.
  virtual ~LookaheadInputSource() = default;
  // peeks character at next nth position.
  virtual uint8_t peek(uint32_t = 0) = 0;
};

class SeekableInputSource : public InputSource {
public:
  // Deconstructor.
  virtual ~SeekableInputSource() = default;

  // Peek forward or backwards.
  virtual uint8_t peek(size_t = 0) = 0;
  // Seeks to exact position given.
  virtual void seek(size_t) const = 0;
  // Seeks from current position to offset.
  virtual void seekTo(size_t) const = 0;
  virtual uint32_t size() const = 0;
};

}; // namespace IO
}; // namespace Z
#endif
