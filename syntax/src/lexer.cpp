#include <Z/Syntax/Lexer>
#include <Z/Syntax/LexerUtil>
#include <Z/Syntax/StringSource>
#include <Z/Syntax/Token>

namespace Z {
namespace Syntax {

Lexer::~Lexer() {}

#define TOKEN(kind)                                                            \
  Token(TokenKind::kind, source.get_line(), source.get_column(), start,        \
        length, source.get_path())

Token Lexer::get() {
  this->skip_trivia();

  this->start = source.get_pos();
  uint32_t ch = source.get();
  uint32_t length = 1;

  switch (ch) {
  case '(':
    return TOKEN(LParen);
  case ')':
    return TOKEN(RParen);
  case '[':
    return TOKEN(LBrak);
  case ']':
    return TOKEN(RBrak);
  case '{':
    return TOKEN(LBrace);
  case '}':
    return TOKEN(RBrace);
  case '.':
    return TOKEN(Dot);
  case ',':
    return TOKEN(Comma);
  case ':':
    return TOKEN(Colon);
  case ';':
    return TOKEN(Semicolon);
  case '^':
    return TOKEN(Caret);
  case '~':
    return TOKEN(Tilde);
  case '+':
    return TOKEN(Plus);
  case '-':
    return TOKEN(Minus);
  case '*':
    return TOKEN(Asterisk);
  case '/':
    return TOKEN(Slash);
  case '%':
    return TOKEN(Percent);
  case '&':
    return TOKEN(Amp);
  case '|':
    return TOKEN(Pipe);
  case '=':
    return TOKEN(Equal);
  case '!':
    return TOKEN(Exclam);
  case '<':
    return TOKEN(Lesser);
  case '>':
    return TOKEN(Greater);
  case '\0':
    return TOKEN(Eof);
  case '"':
  case '\'':
  case '`': {
    length = string_literal(ch);
    return Token(TokenKind::String, this->line, this->col, start, length,
                 source.get_path());
  }
  default: {
    if (LexerUtil::is_unicode_char(ch)) {
    }
    return TOKEN(Dummy);
  }
  }
}

void Lexer::skip_trivia() {
  uint32_t current = 0;
  while (!source.eof()) {
    current = source.peek();
    if (LexerUtil::is_whitespace(current) || LexerUtil::is_linefeed(current)) {
      source.get();
      continue;
    } else if (current == '/') {
      current = source.peek(1);
      if (current == '/') {
        source.get();
        source.get();
        while (!source.eof() && !LexerUtil::is_linefeed(source.get())) {
        }
        continue;
      } else if (current == '*') {
        source.get();
        while (!source.eof()) {
          if (source.peek() == '*' && source.peek(1) == '/') {
            source.get();
            source.get();
            break;
          }
          source.get();
        }
        continue;
      }
    } else {
      break;
    }
  }
}

uint32_t Lexer::string_literal(uint32_t start) {
  uint32_t length = 1;
  while (!eof()) {
    if (source.peek() == '\\') {
      source.get();
      source.get();
      length += 2;
    } else if (source.get() == start) {
      length += 1;
      break;
    }
    length += 1;
  }
  return length;
}

uint32_t Lexer::identifier(uint32_t start) {
  uint32_t length = 0;
  while (!eof()) {
    if (LexerUtil::is_unicode_char(start)) {
      length += 1;
      while (!eof()) {
      }
    } else if (start == '$' && source.peek(1) == '$') {

    } else {
      return 0;
    }
  }
  return length;
}

/** TODO: move to utf8 headers. */
const uint32_t Lexer::utf8_read() {
  uint8_t num_bytes = 1;
  uint32_t code_point = source.peek();

  if ((code_point & 0b10000000) == 0b00000000) {
    num_bytes = 1;
  } else if ((code_point & 0b11100000) == 0b11000000) {
    num_bytes = 2;
    code_point &= 0b00011111;
  } else if ((code_point & 0b11110000) == 0b11100000) {
    num_bytes = 3;
    code_point &= 0b00001111;
  } else if ((code_point & 0b11111000) == 0b11110000) {
    num_bytes = 4;
    code_point &= 0b00000111;
  } else {
    num_bytes = 0;
  }

  for (int i = 1; i < num_bytes; ++i) {
    int next = source.peek(i);
    if (next == 0) {
      // TODO: Error EOF while matching utf8.
      return 0;
    }
    uint8_t c = static_cast<uint8_t>(next);
    if ((c & 0b11000000) != 0b10000000) {
      // TODO: Error Invalid utf8 code point.
      return 0;
    }
    code_point = (code_point << 6) | (c & 0b00111111);
  }

  return code_point;
}

bool Lexer::eof() { return source.eof(); }

#undef TOKEN

} // namespace Syntax
} // namespace Z
