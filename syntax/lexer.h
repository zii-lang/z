#ifndef Z_LEXER_H
#define Z_LEXER_H

#ifdef __cplusplus
#include "token.h"
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iosfwd>
#include <string>
#include <vector>

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
private:
	uint32_t line = 1;
	uint32_t col = 0;

public:
  virtual ~InputSource() = default;

  // peek next char (but don’t advance)
  virtual uint32_t peek() = 0;

  // get next char (advances position)
  virtual uint32_t get() = 0;

  // check if at end
  virtual bool eof() = 0;

	virtual uint32_t get_pos() = 0;
	virtual void set_pos(uint32_t pos) = 0;

  uint32_t get_column() {
		return this->col;
	}

	void set_column(uint32_t col) {
		this->col = col;	
	}
	void inc_column() {
		this->col++;
	}

	uint32_t get_line() {
		return this->line;
	};
	
	void set_line(uint32_t line) {
		this->line = line;
	}

	void inc_line() {
		this->line++;
	}

	virtual const std::string get_path() = 0;
};

/**
 * Buffer of string as source.
 */
class StringSource : public InputSource {
  const std::string &data;
	const std::string path;
  size_t index = 0;

public:
  StringSource(const std::string &str, const std::string path) : data(str), path(path) {}
  uint32_t peek() override;
  uint32_t get() override;
  bool eof() override;
  uint32_t get_pos() override;
	void set_pos(uint32_t) override;
	const std::string get_path() override;
};

/**
 * Buffer of file as source.
 */
class FileSource : public InputSource {
  std::ifstream in;
  std::streampos file_size{0};
	const std::string path;

public:
  FileSource(const std::string &filepath);
  uint32_t peek() override;
  uint32_t get() override;
  bool eof() override;
  uint32_t get_pos() override;
	const std::string get_path() override;
};

class Lexer {
private:
  InputSource &source;
  uint32_t token_count = 0;

	uint32_t start = 0;
	uint32_t line = 0;
	uint32_t col = 1;

public:
  static std::vector<Token> getAll(InputSource &);
  explicit Lexer(InputSource &source) : source(source) {};
  ~Lexer();
  Token peek();
  Token get();
  void advance();
	bool eof();
};

} // namespace Syntax
} // namespace Z

#endif // __cplusplus
#endif // Z_LEXER_H
