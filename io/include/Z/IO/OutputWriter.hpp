#ifndef Z_IO_OUTPUT_WRITER_HPP
#define Z_IO_OUTPUT_WRITER_HPP

#include <cstddef>
#include <cstdint>
#include <string>

namespace Z::IO {

enum class OutputError {
  None = 0b0,
  WriteFailed = 0b1,
  OutOfSpace = 0b10,
  DescriptorError = 0b100,
  Unknown = -1,
};

class OutputWriter {
public:
  OutputWriter() = default;
  virtual ~OutputWriter() = default;
  // Returns the current write position.
  virtual std::size_t pos() const noexcept = 0;

  // Writes a single byte.
  virtual void put(std::uint8_t byte) noexcept = 0;

  // Writes a buffer of data.
  virtual void write(const std::uint8_t *data, std::size_t size) noexcept = 0;
  virtual void write(const std::string data) noexcept = 0;

  // Return the name of descriptor of this writer.
  virtual std::string get_name() const noexcept = 0;
};
}; // namespace Z::IO

#endif
