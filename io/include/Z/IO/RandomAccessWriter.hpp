#ifndef Z_IO_RA_WRITER_HPP
#define Z_IO_RA_WRITER_HPP

#include <Z/IO/OutputWriter.hpp>

namespace Z::IO {
class RandomAccessWriter : public OutputWriter {
	public:
		// Deconstructor.
		virtual ~RandomAccessWriter() = default;

		// Seek to a given position.
		virtual void seek(size_t) const noexcept = 0;
};
}; // namespace Z::IO

#endif
