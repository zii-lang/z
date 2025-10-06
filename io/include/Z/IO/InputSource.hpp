#ifndef Z_IO_INPUT_SOURCE_HPP
#define Z_IO_INPUT_SOURCE_HPP

#include <cstddef>
#include <cstdint>
#include <string_view>

namespace Z {
namespace IO {

/**
 * Interface class for reading a buffer, lexer accept classes that implement
 * this class.
 */
class InputSource {
public:
  virtual ~InputSource() = default;
  virtual uint32_t peek(uint32_t n = 0) = 0;
  virtual uint32_t get() = 0;
  virtual bool eof() = 0;
};

class SeekableInputSource : public InputSource {
public:
  virtual size_t pos() const = 0;
  virtual void seek(size_t pos) = 0;
  virtual uint32_t size() const = 0;
  virtual std::string_view slice(size_t start, size_t length) const = 0;
  // Clear any kind of flags set on file.
  virtual void clear() const = 0;
};

}; // namespace IO
}; // namespace Z
#endif
