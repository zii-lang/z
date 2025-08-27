#ifndef Z_SYNTAX_STRING_SOURCE_HPP
#define Z_SYNTAX_STRING_SOURCE_HPP

#include <Z/Syntax/InputSource>

namespace Z {
namespace Syntax {

/**
 * Buffer of string as source.
 */
class StringSource : public InputSource {
  const std::string data;
  const std::string path;
  size_t index = 0;

public:
  StringSource(const std::string str, const std::string path)
      : data(std::move(str)), path(std::move(path)) {}
  uint32_t peek() override;
  uint32_t peek(uint32_t pos) override;
  uint32_t get() override;
  bool eof() override;
  uint32_t get_pos() override;
  void set_pos(uint32_t) override;
  const std::string get_path() override;
  const std::string slice(uint32_t start, uint32_t length) override;
};

}; // namespace Syntax
}; // namespace Z

#endif
