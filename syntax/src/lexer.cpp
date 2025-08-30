#include "lexer_util.hpp"
#include "utf8_util.hpp"

#include <Z/Syntax/Lexer>
#include <Z/Syntax/StringSource>
#include <Z/Syntax/Token>
#include <Z/Syntax/UTF8Code>
#include <iostream>

namespace Z {
namespace Syntax {

Lexer::~Lexer() {}

#define TOKEN(kind)                                                            \
  Token(TokenKind::kind, source.get_line(), source.get_column(), index,        \
        length, source.get_path())

Token Lexer::get() {
  this->skip_trivia();

  this->index = source.get_pos();
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
    return Token(TokenKind::String, source.get_line(), source.get_column(),
                 index, length, source.get_path());
  }
  default: {
    if (LexerUtil::is_unicode_char(ch)) {
			uint32_t code_length = 0;
			do {
				code_length = Lexer::identifier(ch);
				std::cout << +code_length << std::endl;
				length += code_length;
			} while(code_length > 1);
			length -= 1;
    }
    return TOKEN(Identifier);
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
  UTF8Code code = UTF8Util::utf8_read(source, start);
  length += code.size;
  for (uint32_t i = 0; i < code.size; i++) {
    source.get();
  }
  return length;
}

bool Lexer::eof() { return source.eof(); }

#undef TOKEN

} // namespace Syntax
} // namespace Z
