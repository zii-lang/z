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
  
  size_t pos() const override;
  uint8_t get() const override;
  bool eof() const override;

  uint8_t peek(size_t = 0) override;
  void seek(size_t) const override;
  void seekTo(size_t) const override;
  uint32_t size() const override;
};

}; // namespace IO
}; // namespace Z

#endif
