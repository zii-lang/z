#include "lexer.h"
#include "token.h"
#include <cstdio>

namespace Z {
namespace Syntax {
/**
 * ------------------------------------------
 * StringSource Code
 * ------------------------------------------
 */
// StringSource::StringSource(const std::string &str, const std::string path)
//     : data(str), path(path) {}
uint32_t StringSource::peek() {
  return index < data.size() ? data[index] : '\0';
}

uint32_t StringSource::get() {
  this->inc_column();
  return index < data.size() ? data[index++] : '\0';
}

bool StringSource::eof() { return index >= data.size(); }

uint32_t StringSource::get_pos() { return index; }
void StringSource::set_pos(uint32_t pos) { index = pos; }
const std::string StringSource::get_path() { return this->path; }

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

uint32_t FileSource::get() {
  this->inc_column();
  return eof() ? '\0' : static_cast<uint32_t>(in.get());
}

bool FileSource::eof() { return in.peek() == EOF; }

uint32_t FileSource::get_pos() {
  auto pos = in.tellg();
  return (pos == -1) ? static_cast<size_t>(file_size)
                     : static_cast<size_t>(pos);
}

const std::string FileSource::get_path() { return this->path; }

Lexer::~Lexer() {}

#define TOKEN(kind)                                                            \
  Token(TokenKind::kind, source.get_line(), source.get_column(), start,        \
        length, source.get_path())

Token Lexer::get() {
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

  case '\0':
    return TOKEN(Eof);
  default:
    return TOKEN(Dummy);
  }
}

#undef TOKEN

} // namespace Syntax
} // namespace Z
