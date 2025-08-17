#ifndef Z_LEXER_H
#define Z_LEXER_H
#ifdef __cplusplus

#include <string>
#include <cstdint>
#include <string_view>

enum class LexError {
	InvalidCharacter,
	UnterminatedString,
	UnclosedComment,
	UnclosedCode,
	InvalidEscape,
};

struct lex_file {
	const std::string_view file_name;
	uint32_t line;
	uint32_t maxlines;
};

struct lex_ctx {
	lex_file file;
};

#endif // __cplusplus
#endif // Z_LEXER_H
