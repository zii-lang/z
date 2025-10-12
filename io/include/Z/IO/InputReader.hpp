#ifndef Z_IO_INPUT_SOURCE_HPP
#define Z_IO_INPUT_SOURCE_HPP

#include <cstddef>
#include <cstdint>
#include <string>

namespace Z::IO {

enum class InputError {
  None = 0b0,
  InvalidRead = 0b1,
  InvalidSeek = 0b10,
  InvalidPeek = 0b100,
  EOFReached = 0b1000,
  StreamError = 0b10000,
  MemoryError = 0b100000,
  NullInput = 0b1000000,
  UnknownError = 0b10000000,
};

inline InputError operator&(InputError a, InputError b) {
  return static_cast<InputError>(static_cast<uint32_t>(a) &
                                 static_cast<uint32_t>(b));
}

inline InputError operator|(InputError a, InputError b) {
  return static_cast<InputError>(static_cast<uint32_t>(a) |
                                 static_cast<uint32_t>(b));
}

inline InputError &operator|=(InputError &a, InputError b) {
  a = a | b;
  return a;
}

/**
 * Interface class for reading a buffer, lexer accept classes that implement
 * this class.
 */
class InputReader {
protected:
  mutable InputError _flag = InputError::None;

public:
  virtual ~InputReader() = default;
  virtual size_t pos() const noexcept = 0;
  virtual std::uint8_t get() noexcept = 0;
  virtual std::uint8_t peek(uint32_t = 0) noexcept = 0;
  virtual bool eof() const noexcept = 0;
  virtual std::string get_name() const noexcept = 0;

  inline void setError(InputError flag) const { _flag |= flag; }
  inline bool hasError() const { return _flag != InputError::None; }
  inline bool hasError(InputError flag) const {
    return (_flag & flag) != InputError::None;
  }
  inline void clearError() const { _flag = InputError::None; }
};

}; // namespace Z::IO
#endif
