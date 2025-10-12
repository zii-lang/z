#ifndef Z_SYNTAX_LEXER_HPP
#define Z_SYNTAX_LEXER_HPP

#include <cstdint>

#include <Z/IO.hpp>
#include <Z/Syntax/Token.hpp>

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
  IO::InputReader &reader;
  uint32_t token_count = 0;
  LexError error_code = LexError::NoError;

  std::size_t start = 0;
  std::size_t sline = 0;

  void string_literal(uint32_t start);
  void identifier(uint32_t start);

public:
  explicit Lexer(IO::InputReader &);
  ~Lexer();
  Token peek();
  Token get();
  void advance();
  bool eof();
};

struct LexerFile {
  uint32_t min;
  uint32_t max;
  IO::InputReader &input;
  Lexer &lexer;
};

} // namespace Syntax
} // namespace Z

#endif // Z_SYNTAX_LEXER_HPP
