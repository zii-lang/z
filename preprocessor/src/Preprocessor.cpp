#include <Z/Compiler/Context.hpp>
#include <Z/IO.hpp>
#include <Z/Preprocessor.hpp>
#include <Z/Z.hpp>
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

void Preprocessor::handle_definition() const noexcept {
  if (Util::CharUtil::is_whitespace(_reader.peek())) {
    _reader.advance(1);
  } else {
    // FIX: WTF?
  }

  std::stringstream key;
  std::stringstream value;
  std::uint8_t c = 0;
  bool key_read = false;
  while (!_reader.eof() || !Util::CharUtil::is_linefeed(c = _reader.peek())) {
    if (!key_read) {
      if (Util::CharUtil::is_whitespace(c)) {
        key_read = true;
      } else {
        key.write(reinterpret_cast<CCharPtr>(c), 1);
      }
    } else {
      value.write(reinterpret_cast<CCharPtr>(c), 1);
    }
    _reader.advance(1);
  }

  const std::string trimed_key = Util::StringUtil::trim(key.str());
  std::string trimed_value = Util::StringUtil::trim(value.str());

  if (trimed_value.size() == 0) {
    trimed_value = "1";
  }

  _context.setDefine(trimed_key, trimed_value);
}

Preprocessor::Preprocessor(const IO::InputReader &reader,
                           const Compiler::CompilerContext &context)
    : _reader(reader), _context(context) {}

Preprocessor::~Preprocessor() {}

const PreprocessedSource &Preprocessor::process() {
  std::size_t preOffset = 0;
  std::size_t rawOffset = 0;

  while (!_reader.eof()) {

    this->skip_trivial();

    // A preprocessor directive.
    if (this->_reader.peek() == '#') {
      this->_reader.advance(1);
      std::stringstream stream;
      std::uint8_t c = 0;
      while (!_reader.eof() ||
             Util::CharUtil::is_alpha(c = this->_reader.peek())) {
        stream.write(reinterpret_cast<CCharPtr>(&c), 1);
        this->_reader.advance(1);
      }

      auto dir_search = this->directives.find(stream.str());
      if (dir_search == directives.end()) {
        // FIX: This should probably raise an error for strict preprocessor.
      } else {
        switch (dir_search->second) {
        case DirectiveKind::Define:
          handle_definition();
          break;
        default:
          break;
        }
      }
    } else {
      std::stringstream stream;
      std::uint8_t c = 0;
      preOffset = _reader.pos();
      rawOffset = _output.content.pos();
      while (!_reader.eof() &&
             !Util::CharUtil::is_whitespace(c = this->_reader.peek())) {
        _reader.advance();
        _output.content.put(c);
      }
      _output.mappings.push_back(
          RangeMapping{.preStart = preOffset, .rawStart = rawOffset});
    }
  }

  return _output;
}
}; // namespace Z::PP
