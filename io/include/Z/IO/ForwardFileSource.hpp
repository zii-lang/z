#ifndef Z_IO_FORWARD_FILE_SOURCE_HPP
#define Z_IO_FORWARD_FILE_SOURCE_HPP

#include <Z/IO/InputSource.hpp>

#include <cstdint>
#include <istream>

namespace Z::IO {

class ForwardFileSource : public LookaheadInputSource {
private:
  std::istream *_in;
  size_t _pos = 0;
  bool _ownsStream = false;

public:
  explicit ForwardFileSource(const std::string &path);
  explicit ForwardFileSource(std::istream &stream);
  ~ForwardFileSource();

  size_t pos() const override;
  uint8_t get() override;
  uint8_t peek(uint32_t n = 0) override;
  bool eof() const override;
};

} // namespace Z::IO
  //
#endif
