#ifndef Z_SYNTAX_INPUT_SOURCE_HPP
#define Z_SYNTAX_INPUT_SOURCE_HPP

#include <cstdint>
#include <string>

#include "LexerUtil"

namespace Z {
namespace Syntax {

/**
 * Interface class for reading a buffer, lexer accept classes that implement
 * this class.
 */
class InputSource {
private:
  uint32_t line = 1;
  uint32_t col = 0;

public:
  virtual ~InputSource() = default;

  // peek next char (but don’t advance)
  virtual uint32_t peek() = 0;

  // peek next n characters (won't advance)
  virtual uint32_t peek(uint32_t n) = 0;

  // get next char (advances position)
  virtual uint32_t get() = 0;

  // check if at end
  virtual bool eof() = 0;

  virtual uint32_t get_pos() = 0;
  virtual void set_pos(uint32_t pos) = 0;
  virtual const std::string get_path() = 0;
  virtual const std::string slice(uint32_t start, uint32_t length) = 0;

  uint32_t get_column() { return this->col; }

  void inc_column() {
    if (LexerUtil::is_linefeed(this->peek())) {
      inc_line();
    } else {
      this->col++;
    }
  }

  uint32_t get_line() { return this->line; };

  void inc_line() {
    this->line++;
    this->col = 0;
  }
};

}; // namespace Syntax
}; // namespace Z
#endif
