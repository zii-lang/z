#ifndef Z_IO_STREAM_FILE_READER_HPP
#define Z_IO_STREAM_FILE_READER_HPP

#include <Z/IO/StreamReader.hpp>

#include <cstdint>
#include <istream>

namespace Z::IO {

class StreamFileReader : public StreamReader {
private:
  std::istream *_in;
  size_t _pos = 0;
  bool _ownsStream = false;
  mutable std::string _name = ":stream_file:";

public:
  explicit StreamFileReader(const std::string &path) noexcept;
  explicit StreamFileReader(std::istream &stream) noexcept;
  ~StreamFileReader();

  size_t pos() const noexcept override;
  uint8_t get() noexcept override;
  uint8_t peek(std::size_t = 0) const noexcept override;
  void advance(std::size_t = 0) const noexcept override;
  bool eof() const noexcept override;
  std::string get_name() const noexcept override { return _name; }
  void set_name(std::string) const noexcept;

  std::unique_ptr<RandomAccessReader> toRandomAccess() noexcept override;
};

} // namespace Z::IO
  //
#endif
