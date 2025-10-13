#include <Z/Compiler/Context.hpp>
#include <Z/IO.hpp>
#include <Z/Preprocessor.hpp>
#include <Z/Z.hpp>
#include <iostream>
#include <sstream>
#include <unordered_map>

namespace Z::PP {

void Preprocessor::skip_trivial() const noexcept {
  uint8_t current = 0;
  while (!_reader.eof()) {
    current = _reader.peek();
    if (Util::CharUtil::is_whitespace(current) ||
        Util::CharUtil::is_linefeed(current)) {
      _reader.advance(1);
      continue;
    } else if (current == '/') {
      current = _reader.peek(1);
      if (current == '/') {
        _reader.advance(2);
        while (!_reader.eof() && !Util::CharUtil::is_linefeed(_reader.peek())) {
          _reader.advance(1);
        }
        continue;
      } else if (current == '*') {
        _reader.advance(1);
        while (!_reader.eof()) {
          if (_reader.peek() == '*' && _reader.peek(1) == '/') {
            _reader.advance(2);
            break;
          }
          _reader.advance(1);
        }
        continue;
      }
    } else {
      break;
    }
  }
}

void Preprocessor::handle_definition(const std::string line) const noexcept {
  std::string key;
  std::string value;
  bool key_read = false;
  std::size_t pos = 0;

  while (pos < line.size() && Util::CharUtil::is_alpha(line[pos])) {
    pos++;
  }

  key = line.substr(0, pos);
  value = line.substr(pos + 1, line.size() - pos + 1);

  key = Util::StringUtil::trim(key);
  value = Util::StringUtil::trim(value);

  if (value.size() == 0) {
    value = "1";
  }

  std::cout << "Key: " << key << "\n" << "Value: " << value << std::endl;

  _context.setDefine(key, value);
}

Preprocessor::Preprocessor(const IO::InputReader &reader,
                           const Compiler::CompilerContext &context)
    : _reader(reader), _context(context) {}

Preprocessor::~Preprocessor() {}

const PreprocessedSource &Preprocessor::process() {

  _output.content.seek(0);
  _output.proccessed = true;
  return _output;
}
}; // namespace Z::PP
