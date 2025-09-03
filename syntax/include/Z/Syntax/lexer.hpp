#ifndef Z_SYNTAX_LEXER_HPP
#define Z_SYNTAX_LEXER_HPP

#include "Z/Syntax/input_source.hpp"
#include "Z/Syntax/utf8code.hpp"
#include <cstdint>

#include <Z/Syntax/InputSource>
#include <Z/Syntax/Token>

namespace Z {
namespace Syntax {

enum class LexError {
  NoError = 0,
  InvalidCharacter,
  UnterminatedString,
  UnclosedComment,
  UnclosedCode,
  InvalidEscape,
};

class Lexer {
private:
  InputSource &source;
  uint32_t token_count = 0;
  LexError error_code = LexError::NoError;

  uint32_t start = 0;
	uint32_t sline = 0;

  void skip_trivia();
  void string_literal(uint32_t start);
  UTF8Code identifier(uint32_t start);

public:
  explicit Lexer(InputSource &source) : source(source) {};
  ~Lexer();
  Token peek();
  Token get();
  void advance();
  bool eof();
};

struct LexerFile {
	uint32_t min;
	uint32_t max;
	InputSource& input;
	Lexer& lexer;
};

} // namespace Syntax
} // namespace Z

#endif // Z_SYNTAX_LEXER_HPP
