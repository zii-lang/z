#ifndef Z_IO_MEMORY_READER_HPP
#define Z_IO_MEMORY_READER_HPP

#include <cstddef>
#include <cstring>
#include <string>

#include <Z/IO/RandomAccessReader.hpp>

namespace Z::IO {

class MemoryReader : public RandomAccessReader {
private:
  std::string _buffer;
  std::size_t _pos;
  mutable std::string _name = ":memory:";

public:
  explicit MemoryReader(std::string data);

  // --- InputReader Interface ---
  std::size_t pos() const noexcept override;
  std::uint8_t get() noexcept override;
  std::uint8_t peek(std::uint32_t offset = 0) noexcept override;
  bool eof() const noexcept override;
  std::string get_name() const noexcept override { return _name; }
  void set_name(std::string) const noexcept;

  // --- RandomAccessReader Interface ---
  void seek(std::size_t pos) const noexcept override;
  std::size_t size() const noexcept override;
  std::uint8_t at(std::size_t index) const noexcept override;
};

}; // namespace Z::IO

#endif
