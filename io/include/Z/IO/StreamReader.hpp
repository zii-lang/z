#ifndef Z_IO_STREAM_READER_HPP
#define Z_IO_STREAM_READER_HPP

#include <memory>

#include <Z/IO/InputReader.hpp>

namespace Z::IO {

/**
 * Forward only, Lookahead source stream.
 */
class StreamReader : public InputReader {
public:
  // Deconstructor.
  virtual ~StreamReader() = default;

  virtual std::unique_ptr<class RandomAccessReader>
  toRandomAccess() noexcept = 0;
};

}; // namespace Z::IO

#endif
