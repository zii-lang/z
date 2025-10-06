#ifndef Z_IO_FILE_SOURCE_HPP
#define Z_IO_FILE_SOURCE_HPP

#include <fstream>
#include <iosfwd>

#include <Z/IO/InputSource.hpp>

namespace Z {
namespace IO {
/**
 * Buffer of file as source.
 */
class FileSource : public SeekableInputSource {
  mutable std::ifstream _in;
  size_t _size;

public:
  FileSource(const std::string &filepath);

  // --- InputSource Methods ---
  /* peeks next `n`th character and returns it. */
  uint32_t peek(uint32_t n = 0) override;
  /* advances and return the character at current position. */
  uint32_t get() override;
  /* indicates end of file. */
  bool eof() override;

  // --- SeekableInputSource Methods ---
  size_t pos() const override;
  void seek(size_t pos, SeekKind kind) override;
  uint32_t size() const override;
  std::string slice(size_t start, size_t length) const override;
  void clear() const override;
};

}; // namespace IO
}; // namespace Z

#endif
