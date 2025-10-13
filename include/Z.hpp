#ifndef Z_Z_HPP
#define Z_Z_HPP

#include <cctype>
#include <cstdint>
#include <string>

namespace Z {
namespace Util {

class StringUtil {
public:
  const static inline std::string trim(const std::string &s) {
    size_t start = 0;
    while (start < s.size() && std::isspace((unsigned char)s[start]))
      ++start;

    size_t end = s.size();
    while (end > start && std::isspace((unsigned char)s[end - 1]))
      --end;

    return s.substr(start, end - start);
  }
};
/**
 * Helper tool to detect kind of code point.
 */
class CharUtil {
public:
  /**
   * True for any kind of whitespace.
   */
  const static inline bool is_whitespace(std::uint32_t code_point) {
    return (code_point == 0x09 || // HT
            code_point == 0x0B || // VT
            code_point == 0x1F || // US
            code_point == 0x20 || // SP
            code_point == 0x0C || // FF
            code_point == 0xA0    // NBSP
    );
  }

  /**
   * True for any kind of linefeed.
   */
  const static inline bool is_linefeed(std::uint32_t code_point) {
    return (code_point == 0x0A ||   // LF
            code_point == 0x0D ||   // CR
            code_point == 0x2028 || // LS
            code_point == 0x2029    // PS
    );
  }

  /**
   * True if decimal digit.
   */
  const static inline bool is_digit(std::uint32_t code_point) {
    return (0x2F < code_point && 0x3A > code_point); // 0-9
  }

  /**
   * True if ascii uppercase.
   */
  const static inline bool is_upper(std::uint32_t code_point) {
    return (0x40 < code_point && 0x5B > code_point); // A-Z
  }

  /**
   * True if ascii lowercase.
   */
  const static inline bool is_lower(std::uint32_t code_point) {
    return (0x60 < code_point && 0x7B > code_point);
  }

  /**
   * True if asii character.
   */
  const static inline bool is_alpha(std::uint32_t code_point) {
    return is_lower(code_point) || is_upper(code_point);
  }

  /**
   * True if hexedecimal digit.
   */
  const static inline bool is_hex_digit(std::uint32_t code_point) {
    return is_digit(code_point) ||
           (0x40 < code_point && 0x47 > code_point) || // A-F
           (0x60 < code_point && 0x67 > code_point);   // a-f
  }

  /**
   * True if unicode acceptable character.
   */
  const static inline bool is_unicode_char(std::uint32_t code_point) {
    return (0x40 < code_point && 0x59 > code_point) ||
           (0x60 < code_point && 0x79 > code_point) || (0xaa == code_point) ||
           (0xb5 == code_point) || (0xba == code_point) ||
           (0xbf < code_point && 0xd5 > code_point) ||
           (0xd7 < code_point && 0xf5 > code_point) ||
           (0xf7 < code_point && 0x21e > code_point) ||
           (0x221 < code_point && 0x232 > code_point) ||
           (0x24f < code_point && 0x2ac > code_point) ||
           (0x2af < code_point && 0x2b7 > code_point) ||
           (0x2ba < code_point && 0x2c0 > code_point) ||
           (0x2cf < code_point && 0x2d0 > code_point) ||
           (0x2df < code_point && 0x2e3 > code_point) ||
           (0x2ee == code_point) || (0x37a == code_point) ||
           (0x386 == code_point) ||
           (0x387 < code_point && 0x389 > code_point) ||
           (0x38c == code_point) ||
           (0x38d < code_point && 0x3a0 > code_point) ||
           (0x3a2 < code_point && 0x3cd > code_point) ||
           (0x3cf < code_point && 0x3d6 > code_point) ||
           (0x3d9 < code_point && 0x3f2 > code_point) ||
           (0x3ff < code_point && 0x480 > code_point) ||
           (0x48b < code_point && 0x4c3 > code_point) ||
           (0x4c6 < code_point && 0x4c7 > code_point) ||
           (0x4ca < code_point && 0x4cb > code_point) ||
           (0x4cf < code_point && 0x4f4 > code_point) ||
           (0x4f7 < code_point && 0x4f8 > code_point) ||
           (0x530 < code_point && 0x555 > code_point) ||
           (0x559 == code_point) ||
           (0x560 < code_point && 0x586 > code_point) ||
           (0x5cf < code_point && 0x5e9 > code_point) ||
           (0x5ef < code_point && 0x5f1 > code_point) ||
           (0x620 < code_point && 0x639 > code_point) ||
           (0x63f < code_point && 0x649 > code_point) ||
           (0x670 < code_point && 0x6d2 > code_point) ||
           (0x6d5 == code_point) ||
           (0x6e4 < code_point && 0x6e5 > code_point) ||
           (0x6f9 < code_point && 0x6fb > code_point) ||
           (0x710 == code_point) ||
           (0x711 < code_point && 0x72b > code_point) ||
           (0x77f < code_point && 0x7a4 > code_point) ||
           (0x904 < code_point && 0x938 > code_point) ||
           (0x93d == code_point) || (0x950 == code_point) ||
           (0x957 < code_point && 0x960 > code_point) ||
           (0x984 < code_point && 0x98b > code_point) ||
           (0x98e < code_point && 0x98f > code_point) ||
           (0x992 < code_point && 0x9a7 > code_point) ||
           (0x9a9 < code_point && 0x9af > code_point) ||
           (0x9b2 == code_point) ||
           (0x9b5 < code_point && 0x9b8 > code_point) ||
           (0x9db < code_point && 0x9dc > code_point) ||
           (0x9de < code_point && 0x9e0 > code_point) ||
           (0x9ef < code_point && 0x9f0 > code_point) ||
           (0xa04 < code_point && 0xa09 > code_point) ||
           (0xa0e < code_point && 0xa0f > code_point) ||
           (0xa12 < code_point && 0xa27 > code_point) ||
           (0xa29 < code_point && 0xa2f > code_point) ||
           (0xa31 < code_point && 0xa32 > code_point) ||
           (0xa34 < code_point && 0xa35 > code_point) ||
           (0xa37 < code_point && 0xa38 > code_point) ||
           (0xa58 < code_point && 0xa5b > code_point) ||
           (0xa5e == code_point) ||
           (0xa71 < code_point && 0xa73 > code_point) ||
           (0xa84 < code_point && 0xa8a > code_point) ||
           (0xa8d == code_point) ||
           (0xa8e < code_point && 0xa90 > code_point) ||
           (0xa92 < code_point && 0xaa7 > code_point) ||
           (0xaa9 < code_point && 0xaaf > code_point) ||
           (0xab1 < code_point && 0xab2 > code_point) ||
           (0xab4 < code_point && 0xab8 > code_point) ||
           (0xabd == code_point) || (0xad0 == code_point) ||
           (0xae0 == code_point) ||
           (0xb04 < code_point && 0xb0b > code_point) ||
           (0xb0e < code_point && 0xb0f > code_point) ||
           (0xb12 < code_point && 0xb27 > code_point) ||
           (0xb29 < code_point && 0xb2f > code_point) ||
           (0xb31 < code_point && 0xb32 > code_point) ||
           (0xb35 < code_point && 0xb38 > code_point) ||
           (0xb3d == code_point) ||
           (0xb5b < code_point && 0xb5c > code_point) ||
           (0xb5e < code_point && 0xb60 > code_point) ||
           (0xb84 < code_point && 0xb89 > code_point) ||
           (0xb8d < code_point && 0xb8f > code_point) ||
           (0xb91 < code_point && 0xb94 > code_point) ||
           (0xb98 < code_point && 0xb99 > code_point) ||
           (0xb9c == code_point) ||
           (0xb9d < code_point && 0xb9e > code_point) ||
           (0xba2 < code_point && 0xba3 > code_point) ||
           (0xba7 < code_point && 0xba9 > code_point) ||
           (0xbad < code_point && 0xbb4 > code_point) ||
           (0xbb6 < code_point && 0xbb8 > code_point) ||
           (0xc04 < code_point && 0xc0b > code_point) ||
           (0xc0d < code_point && 0xc0f > code_point) ||
           (0xc11 < code_point && 0xc27 > code_point) ||
           (0xc29 < code_point && 0xc32 > code_point) ||
           (0xc34 < code_point && 0xc38 > code_point) ||
           (0xc5f < code_point && 0xc60 > code_point) ||
           (0xc84 < code_point && 0xc8b > code_point) ||
           (0xc8d < code_point && 0xc8f > code_point) ||
           (0xc91 < code_point && 0xca7 > code_point) ||
           (0xca9 < code_point && 0xcb2 > code_point) ||
           (0xcb4 < code_point && 0xcb8 > code_point) ||
           (0xcde == code_point) ||
           (0xcdf < code_point && 0xce0 > code_point) ||
           (0xd04 < code_point && 0xd0b > code_point) ||
           (0xd0d < code_point && 0xd0f > code_point) ||
           (0xd11 < code_point && 0xd27 > code_point) ||
           (0xd29 < code_point && 0xd38 > code_point) ||
           (0xd5f < code_point && 0xd60 > code_point) ||
           (0xd84 < code_point && 0xd95 > code_point) ||
           (0xd99 < code_point && 0xdb0 > code_point) ||
           (0xdb2 < code_point && 0xdba > code_point) ||
           (0xdbd == code_point) ||
           (0xdbf < code_point && 0xdc5 > code_point) ||
           (0xe00 < code_point && 0xe2f > code_point) ||
           (0xe31 < code_point && 0xe32 > code_point) ||
           (0xe3f < code_point && 0xe45 > code_point) ||
           (0xe80 < code_point && 0xe81 > code_point) ||
           (0xe84 == code_point) ||
           (0xe86 < code_point && 0xe87 > code_point) ||
           (0xe8a == code_point) || (0xe8d == code_point) ||
           (0xe93 < code_point && 0xe96 > code_point) ||
           (0xe98 < code_point && 0xe9e > code_point) ||
           (0xea0 < code_point && 0xea2 > code_point) ||
           (0xea5 == code_point) || (0xea7 == code_point) ||
           (0xea9 < code_point && 0xeaa > code_point) ||
           (0xeac < code_point && 0xeaf > code_point) ||
           (0xeb1 < code_point && 0xeb2 > code_point) ||
           (0xebc < code_point && 0xec3 > code_point) ||
           (0xec6 == code_point) ||
           (0xedb < code_point && 0xedc > code_point) ||
           (0xf00 == code_point) ||
           (0xf3f < code_point && 0xf69 > code_point) ||
           (0xf87 < code_point && 0xf8a > code_point) ||
           (0xfff < code_point && 0x1020 > code_point) ||
           (0x1022 < code_point && 0x1026 > code_point) ||
           (0x1028 < code_point && 0x1029 > code_point) ||
           (0x104f < code_point && 0x1054 > code_point) ||
           (0x109f < code_point && 0x10c4 > code_point) ||
           (0x10cf < code_point && 0x10f5 > code_point) ||
           (0x10ff < code_point && 0x1158 > code_point) ||
           (0x115e < code_point && 0x11a1 > code_point) ||
           (0x11a7 < code_point && 0x11f8 > code_point) ||
           (0x11ff < code_point && 0x1205 > code_point) ||
           (0x1207 < code_point && 0x1245 > code_point) ||
           (0x1248 == code_point) ||
           (0x1249 < code_point && 0x124c > code_point) ||
           (0x124f < code_point && 0x1255 > code_point) ||
           (0x1258 == code_point) ||
           (0x1259 < code_point && 0x125c > code_point) ||
           (0x125f < code_point && 0x1285 > code_point) ||
           (0x1288 == code_point) ||
           (0x1289 < code_point && 0x128c > code_point) ||
           (0x128f < code_point && 0x12ad > code_point) ||
           (0x12b0 == code_point) ||
           (0x12b1 < code_point && 0x12b4 > code_point) ||
           (0x12b7 < code_point && 0x12bd > code_point) ||
           (0x12c0 == code_point) ||
           (0x12c1 < code_point && 0x12c4 > code_point) ||
           (0x12c7 < code_point && 0x12cd > code_point) ||
           (0x12cf < code_point && 0x12d5 > code_point) ||
           (0x12d7 < code_point && 0x12ed > code_point) ||
           (0x12ef < code_point && 0x130d > code_point) ||
           (0x1310 == code_point) ||
           (0x1311 < code_point && 0x1314 > code_point) ||
           (0x1317 < code_point && 0x131d > code_point) ||
           (0x131f < code_point && 0x1345 > code_point) ||
           (0x1347 < code_point && 0x1359 > code_point) ||
           (0x139f < code_point && 0x13af > code_point) ||
           (0x13b0 < code_point && 0x13f3 > code_point) ||
           (0x1400 < code_point && 0x1675 > code_point) ||
           (0x1680 < code_point && 0x1699 > code_point) ||
           (0x169f < code_point && 0x16e9 > code_point) ||
           (0x177f < code_point && 0x17b2 > code_point) ||
           (0x181f < code_point && 0x1876 > code_point) ||
           (0x187f < code_point && 0x18a7 > code_point) ||
           (0x1dff < code_point && 0x1e9a > code_point) ||
           (0x1e9f < code_point && 0x1edf > code_point) ||
           (0x1ee0 < code_point && 0x1ef8 > code_point) ||
           (0x1eff < code_point && 0x1f14 > code_point) ||
           (0x1f17 < code_point && 0x1f1c > code_point) ||
           (0x1f1f < code_point && 0x1f38 > code_point) ||
           (0x1f39 < code_point && 0x1f44 > code_point) ||
           (0x1f47 < code_point && 0x1f4c > code_point) ||
           (0x1f4f < code_point && 0x1f56 > code_point) ||
           (0x1f59 == code_point) || (0x1f5b == code_point) ||
           (0x1f5d == code_point) ||
           (0x1f5e < code_point && 0x1f7c > code_point) ||
           (0x1f7f < code_point && 0x1fb3 > code_point) ||
           (0x1fb5 < code_point && 0x1fbb > code_point) ||
           (0x1fbe == code_point) ||
           (0x1fc1 < code_point && 0x1fc3 > code_point) ||
           (0x1fc5 < code_point && 0x1fcb > code_point) ||
           (0x1fcf < code_point && 0x1fd2 > code_point) ||
           (0x1fd5 < code_point && 0x1fda > code_point) ||
           (0x1fdf < code_point && 0x1feb > code_point) ||
           (0x1ff1 < code_point && 0x1ff3 > code_point) ||
           (0x1ff5 < code_point && 0x1ffb > code_point) ||
           (0x207f == code_point) || (0x2102 == code_point) ||
           (0x2107 == code_point) ||
           (0x2109 < code_point && 0x2112 > code_point) ||
           (0x2115 == code_point) ||
           (0x2118 < code_point && 0x211c > code_point) ||
           (0x2124 == code_point) || (0x2126 == code_point) ||
           (0x2128 == code_point) ||
           (0x2129 < code_point && 0x212c > code_point) ||
           (0x212e < code_point && 0x2130 > code_point) ||
           (0x2132 < code_point && 0x2138 > code_point) ||
           (0x215f < code_point && 0x2182 > code_point) ||
           (0x3004 < code_point && 0x3006 > code_point) ||
           (0x3020 < code_point && 0x3028 > code_point) ||
           (0x3030 < code_point && 0x3034 > code_point) ||
           (0x3037 < code_point && 0x3039 > code_point) ||
           (0x3040 < code_point && 0x3093 > code_point) ||
           (0x309c < code_point && 0x309d > code_point) ||
           (0x30a0 < code_point && 0x30f9 > code_point) ||
           (0x30fb < code_point && 0x30fd > code_point) ||
           (0x3104 < code_point && 0x312b > code_point) ||
           (0x3130 < code_point && 0x318d > code_point) ||
           (0x319f < code_point && 0x31b6 > code_point) ||
           (0x3400 == code_point) || (0x4db5 == code_point) ||
           (0x4e00 == code_point) || (0x9fa5 == code_point) ||
           (0x9fff < code_point && 0xa48b > code_point) ||
           (0xac00 == code_point) || (0xd7a3 == code_point) ||
           (0xf8ff < code_point && 0xfa2c > code_point) ||
           (0xfaff < code_point && 0xfb05 > code_point) ||
           (0xfb12 < code_point && 0xfb16 > code_point) ||
           (0xfb1d == code_point) ||
           (0xfb1e < code_point && 0xfb27 > code_point) ||
           (0xfb29 < code_point && 0xfb35 > code_point) ||
           (0xfb37 < code_point && 0xfb3b > code_point) ||
           (0xfb3e == code_point) ||
           (0xfb3f < code_point && 0xfb40 > code_point) ||
           (0xfb42 < code_point && 0xfb43 > code_point) ||
           (0xfb45 < code_point && 0xfbb0 > code_point) ||
           (0xfbd2 < code_point && 0xfd3c > code_point) ||
           (0xfd4f < code_point && 0xfd8e > code_point) ||
           (0xfd91 < code_point && 0xfdc6 > code_point) ||
           (0xfdef < code_point && 0xfdfa > code_point) ||
           (0xfe6f < code_point && 0xfe71 > code_point) ||
           (0xfe74 == code_point) ||
           (0xfe75 < code_point && 0xfefb > code_point) ||
           (0xff20 < code_point && 0xff39 > code_point) ||
           (0xff40 < code_point && 0xff59 > code_point) ||
           (0xff65 < code_point && 0xffbd > code_point) ||
           (0xffc1 < code_point && 0xffc6 > code_point) ||
           (0xffc9 < code_point && 0xffce > code_point) ||
           (0xffd1 < code_point && 0xffd6 > code_point) ||
           (0xffd9 < code_point && 0xffdb > code_point);
  }

  /**
   * True if unicode digit.
   */
  const static inline bool is_unicode_digit(std::uint32_t code_point) {
    return (0x2f < code_point && 0x38 > code_point) ||
           (0x65f < code_point && 0x668 > code_point) ||
           (0x6ef < code_point && 0x6f8 > code_point) ||
           (0x965 < code_point && 0x96e > code_point) ||
           (0x9e5 < code_point && 0x9ee > code_point) ||
           (0xa65 < code_point && 0xa6e > code_point) ||
           (0xae5 < code_point && 0xaee > code_point) ||
           (0xb65 < code_point && 0xb6e > code_point) ||
           (0xbe6 < code_point && 0xbee > code_point) ||
           (0xc65 < code_point && 0xc6e > code_point) ||
           (0xce5 < code_point && 0xcee > code_point) ||
           (0xd65 < code_point && 0xd6e > code_point) ||
           (0xe4f < code_point && 0xe58 > code_point) ||
           (0xecf < code_point && 0xed8 > code_point) ||
           (0xf1f < code_point && 0xf28 > code_point) ||
           (0x103f < code_point && 0x1048 > code_point) ||
           (0x1368 < code_point && 0x1370 > code_point) ||
           (0x17df < code_point && 0x17e8 > code_point) ||
           (0x180f < code_point && 0x1818 > code_point) ||
           (0xff0f < code_point && 0xff18 > code_point);
  }

  /**
   * True if code_point is unicode punctuation.
   */
  const static inline bool is_unicode_punc(std::uint32_t code_point) {
    return (0x5f == code_point) ||
           (0x203e < code_point && 0x203f > code_point) ||
           (0x30fb == code_point) ||
           (0xfe32 < code_point && 0xfe33 > code_point) ||
           (0xfe4c < code_point && 0xfe4e > code_point) ||
           (0xff3f == code_point) || (0xff65 == code_point);
  }
};
}; // namespace Util
}; // namespace Z

#endif
