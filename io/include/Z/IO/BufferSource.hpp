#ifndef Z_IO_BUFFER_SOURCE_HPP
#define Z_IO_BUFFER_SOURCE_HPP

#include "Z/IO/InputSource.hpp"
#include <vector>

namespace Z {
namespace IO {
class BufferSource : public LookaheadInputSource {
private:
  LookaheadInputSource &_inner;
  std::vector<uint8_t> _buffer;
  size_t _start_pos;
  size_t _cursor;

public:
  BufferSource(LookaheadInputSource &);

  uint8_t peek(uint32_t = 0) override;
};
}; // namespace IO
}; // namespace Z

#endif
