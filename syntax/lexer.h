#ifndef Z_LEXER_H
#define Z_LEXER_H

#include "token.h"
#include <vector>
#ifdef __cplusplus

#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iosfwd>
#include <string>

namespace Z {
namespace Syntax {

enum class LexError {
  InvalidCharacter,
  UnterminatedString,
  UnclosedComment,
  UnclosedCode,
  InvalidEscape,
};

/**
 * Interface class for reading a buffer, lexer accept classes that implement
 * this class.
 */
class InputSource {
public:
  virtual ~InputSource() = default;

  // peek next char (but don’t advance)
  virtual uint32_t peek() = 0;

  // get next char (advances position)
  virtual uint32_t get() = 0;

  // check if at end
  virtual bool eof() = 0;

  // optional: get position info
  virtual size_t position() = 0;
};

/**
 * Buffer of string as source.
 */
class StringSource : public InputSource {
  const std::string &data;
  size_t index = 0;

public:
  StringSource(const std::string &str);
  uint32_t peek() override;
  uint32_t get() override;
  bool eof() override;
  size_t position() override;
};

/**
 * Buffer of file as source.
 */
class FileSource : public InputSource {
  std::ifstream in;
  std::streampos file_size{0};

public:
  FileSource(const std::string &filepath);
  uint32_t peek() override;
  uint32_t get() override;
  bool eof() override;
  size_t position() override;
};

class Lexer {
public:
  static std::vector<Token> getAll(InputSource &);
  explicit Lexer(InputSource &);
  ~Lexer();
  Token peek();
  Token get();
  void advance();
};

} // namespace Syntax
} // namespace Z

#endif // __cplusplus
#endif // Z_LEXER_H
