#ifndef Z_IO_RA_READER_HPP
#define Z_IO_RA_READER_HPP

#include <Z/IO/InputReader.hpp>

namespace Z::IO {

class RandomAccessReader : public InputReader {
public:
  // Deconstructor.
  virtual ~RandomAccessReader() = default;
  // Seeks to exact position given.
  virtual void seek(size_t) const noexcept = 0;
  virtual std::size_t size() const noexcept = 0;
  virtual uint8_t at(size_t) const noexcept = 0;
};

}; // namespace Z::IO

#endif
