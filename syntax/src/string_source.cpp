#include "lexer_util.hpp"

#include <Z/Syntax/StringSource>

namespace Z {
namespace Syntax {

uint32_t StringSource::peek() {
  return index < data.size() ? data[index] : '\0';
}

uint32_t StringSource::peek(uint32_t n) {
  return (index + n) < data.size() ? data[index + n] : '\0';
}

uint32_t StringSource::get() {
  this->inc_pos();
  return index < data.size() ? data[index++] : '\0';
}

bool StringSource::eof() { return index >= data.size(); }

uint32_t StringSource::get_pos() { return index; }

void StringSource::set_pos(uint32_t pos) { index = pos; }

void StringSource::inc_pos() {
	this->length += 1;
  if (LexerUtil::is_linefeed(this->peek())) {
    inc_line();
  }
}

uint32_t StringSource::get_line() { return this->line; }

void StringSource::inc_line() { this->line += 1; }

uint32_t StringSource::get_length() { return this->length; }
void StringSource::clear() { this->length = 0; }

const std::string StringSource::get_path() { return this->path; }
const std::string StringSource::slice(uint32_t start, uint32_t length) {
  if (start >= data.size())
    return {};
  return data.substr(start, length);
}

}; // namespace Syntax
}; // namespace Z
