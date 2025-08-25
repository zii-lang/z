#ifdef __cplusplus

#include "lexer.h"
#include "token.h"
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

namespace Z {
namespace Syntax {

/**
 * ------------------------------------------
 * StringSource Code
 * ------------------------------------------
 */
uint32_t StringSource::peek() {
  return index < data.size() ? data[index] : '\0';
}

uint32_t StringSource::peek(uint32_t n) {
  return (index + n) < data.size() ? data[index + n] : '\0';
}

uint32_t StringSource::get() {
  this->inc_column();
  return index < data.size() ? data[index++] : '\0';
}

bool StringSource::eof() { return index >= data.size(); }

uint32_t StringSource::get_pos() { return index; }
void StringSource::set_pos(uint32_t pos) { index = pos; }
const std::string StringSource::get_path() { return this->path; }
const std::string StringSource::slice(uint32_t start, uint32_t length) {
  if (start >= data.size())
    return {};
  return data.substr(start, std::min<uint32_t>(length, data.size() - start));
}

/**
 * ------------------------------------------
 *  FileSource
 * ------------------------------------------
 */
FileSource::FileSource(const std::string &filepath)
    : in(filepath, std::ios::binary), path(filepath) {
  if (!in.is_open()) {
    throw std::runtime_error("Cannot open file: " + filepath);
  }
  in.seekg(0, std::ios::end);
  file_size = in.tellg();
  in.seekg(0, std::ios::beg);
}

uint32_t FileSource::peek() {
  return eof() ? '\0' : static_cast<uint32_t>(in.peek());
}

uint32_t FileSource::peek(uint32_t n) {
  if ((static_cast<uint32_t>(in.tellg()) + 0) < file_size) {
    in.seekg(n, std::ios::cur);
    const uint32_t ch = in.peek();
    in.seekg(-static_cast<int32_t>(n), std::ios::cur);
    return ch;
  } else {
    return '\0';
  }
}

uint32_t FileSource::get() {
  this->inc_column();
  return eof() ? '\0' : static_cast<uint32_t>(in.get());
}

bool FileSource::eof() { return in.peek() == EOF; }

uint32_t FileSource::get_pos() {
  auto pos = in.tellg();
  return (pos == -1) ? static_cast<uint32_t>(file_size)
                     : static_cast<uint32_t>(pos);
}

void FileSource::set_pos(uint32_t pos) { in.seekg(pos, std::ios::beg); }

const std::string FileSource::get_path() { return this->path; }

const std::string FileSource::slice(uint32_t start, uint32_t length) {
  in.seekg(0, std::ios::end);
  size_t file_size = in.tellg();
  if (start >= file_size)
    return {};

  in.seekg(start, std::ios::beg);
  std::string buffer(std::min<uint32_t>(length, file_size - start), '\0');
  in.read(buffer.data(), buffer.size());
  buffer.resize(in.gcount());
  return buffer;
}

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
  default:
    return TOKEN(Dummy);
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

bool Lexer::eof() { return source.eof(); }

#undef TOKEN

} // namespace Syntax
} // namespace Z
#endif // __cplusplus
