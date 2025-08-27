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

}; // namespace Syntax
}; // namespace Z
