#include <Z/Compiler/Context.hpp>
#include <Z/IO.hpp>

namespace Z::PP {

class Preprocessor {
public:
  explicit Preprocessor(IO::MemoryReader &reader);
};

}; // namespace Z::PP
