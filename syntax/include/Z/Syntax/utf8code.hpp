#ifndef Z_SYNTAX_UTF8CODE_HPP
#define Z_SYNTAX_UTF8CODE_HPP

#include <cstdint>

namespace Z {
namespace Syntax {
struct UTF8Code {
  uint8_t size;
  uint32_t code;
  UTF8Code(uint8_t size, uint32_t code): size(size), code(code) {};
};
} // namespace Syntax
} // namespace Z
#endif
