/*
#include "Z/Syntax/Token.hpp"
#include "lexer_util.hpp"
#include "utf8_util.hpp"

#include <Z/Syntax/Lexer>
#include <Z/Syntax/StringSource>
#include <Z/Syntax/Token>
#include <Z/Syntax/UTF8Code>

#include <iostream>
#include <unordered_map>

namespace Z {
namespace Syntax {

Lexer::~Lexer() {}

#define TOKEN(kind)                                                            \
  Token(TokenKind::kind, this->sline, source.get_line(), start,                \
        this->start + source.get_length(), source.get_length(),                \
        source.get_path())

Token Lexer::get() {
  source.clear();
  this->skip_trivia();
  this->start = source.get_pos();
  this->sline = source.get_line();
  uint32_t ch = source.get();

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
    if (source.peek() == '=') {
      source.get();
      return TOKEN(ColonEqual);
    }
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
        case '$':
                if( source.peek() == '$') {
                        uint32_t ch2 = source.peek(1);
                        if( ch2 == '"' || ch2 == '\'' || ch2 == '`') {
                                source.get();
                                source.get();
                                string_literal(ch2);
                                return Token(TokenKind::Identifier, this->sline,
source.get_line(), this->start, this->start + source.get_length() - 1,
source.get_length() - 1, source.get_path());
                        }
                }
  case '\0':
    return TOKEN(Eof);
  case '"':
  case '\'':
  case '`': {
    string_literal(ch);
    return Token(TokenKind::String, this->sline, source.get_line(), this->start,
                 this->start + source.get_length(), source.get_length(),
                 source.get_path());
  }
  default: {
    if (LexerUtil::is_unicode_char(ch)) {
      uint32_t size = Lexer::identifier(ch).size;
      for (uint32_t i = 1; i < size; i++) {
        ch = source.get();
      }
                        std::cout << +ch << std::endl;
      while ((LexerUtil::is_unicode_char(ch) ||
              LexerUtil::is_unicode_digit(ch) ||
              LexerUtil::is_unicode_punc(ch))) {
        size = Lexer::identifier(ch).size;
        for (uint32_t i = 0; i < size; i++) {
          ch = source.get();
        }
      }
      const std::string tempLiteral =
          source.slice(this->start, source.get_length());
      if (auto search = Keywords.find(tempLiteral); search != Keywords.end()) {
        return Token(search->second, this->sline, source.get_line(),
                     this->start, this->start + source.get_length(),
                     source.get_length(), source.get_path());
      }
      return Token(TokenKind::Identifier, this->sline, source.get_line(),
                   this->start, this->start + source.get_length(),
                   source.get_length(), source.get_path());
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

void Lexer::string_literal(uint32_t start) {
  while (!eof()) {
    if (source.peek() == '\\') {
      source.get();
      source.get();
    } else if (source.get() == start) {
      break;
    }
  }
}

UTF8Code Lexer::identifier(uint32_t start) {
  return UTF8Util::utf8_read(source, start);
}

bool Lexer::eof() { return source.eof(); }

#undef TOKEN

} // namespace Syntax
} // namespace Z
*/
