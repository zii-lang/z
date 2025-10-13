#ifndef Z_IO_MEMORY_WRITER_HPP
#define Z_IO_MEMORY_WRITER_HPP

#include <Z/IO/InputReader.hpp>
#include <Z/IO/RandomAccess/MemoryReader.hpp>
#include <Z/IO/RandomAccessWriter.hpp>
#include <Z/Z.hpp>
#include <sstream>

namespace Z::IO {
class MemoryWriter : public RandomAccessWriter {
private:
  std::string _name = ":mem:";
  std::ostringstream output;

public:
  explicit MemoryWriter() {}
  explicit MemoryWriter(std::string name) : _name(name) {}

  std::size_t pos() const noexcept override { return output.cur; }

  void put(std::uint8_t byte) noexcept override {
    output.write(reinterpret_cast<const char *>(&byte), 1);
    output.flush();
  }

  void write(const std::uint8_t *data, std::size_t size) noexcept override {
    output.write(reinterpret_cast<const char *>(data), size);
    output.flush();
  }

  void write(const std::string data) noexcept override {
    output << data;
    output.flush();
  }

  std::string get_name() const noexcept override { return this->_name; }

  MemoryReader toReader() {
    MemoryReader reader(output.str());
    reader.seek(0);
    return reader;
  }

  void seek(size_t pos) const noexcept override {
    const_cast<std::ostringstream &>(output).seekp(pos);
  }
};
}; // namespace Z::IO

#endif
