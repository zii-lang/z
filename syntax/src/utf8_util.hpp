#ifndef Z_SYNTAX_UTF8_UTIL_HPP
#define Z_SYNTAX_UTF8_UTIL_HPP

#include <Z/Syntax/InputSource>
#include <Z/Syntax/UTF8Code>

#include <cstdint>

namespace Z {
namespace Syntax {
class UTF8Util {
public:
  static const UTF8Code utf8_read(InputSource &source) {
    return utf8_read(source, source.peek());
  }

  static const UTF8Code utf8_read(InputSource &source, uint32_t start) {
    UTF8Code cp = {1, start};

    if ((cp.code & 0b10000000) == 0b00000000) {
      cp.size = 1;
    } else if ((cp.code & 0b11100000) == 0b11000000) {
      cp.size = 2;
      cp.code &= 0b00011111;
    } else if ((cp.code & 0b11110000) == 0b11100000) {
      cp.size = 3;
      cp.code &= 0b00001111;
    } else if ((cp.code & 0b11111000) == 0b11110000) {
      cp.size = 4;
      cp.code &= 0b00000111;
    } else {
      cp.size = 0;
    }

    for (uint32_t i = 1; i < cp.size; i++) {
      uint32_t next = source.peek(i-1);
      if (next == 0) {
        // TODO: Error EOF while matching utf8.
        cp.size = 0;
        return cp;
      }
      uint8_t c = static_cast<uint8_t>(next);
      if ((c & 0b11000000) != 0b10000000) {
        // TODO: Error Invalid utf8 code point.
        cp.size = 0;
        return cp;
      }
      cp.code = (cp.code << 6) | (c & 0b00111111);
    }

    return cp;
  }
};
} // namespace Syntax
} // namespace Z

#endif
