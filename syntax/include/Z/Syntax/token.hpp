#ifndef Z_SYNTAX_TOKEN_HPP
#define Z_SYNTAX_TOKEN_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>

namespace Z {
namespace Syntax {
/**
 * Type of token for lexical analysis.
 */
enum class TokenKind {
  Dummy = -2,
  Eof = -1,
  Plus = 1,
  Minus,
  Asterisk,
  Slash,
  Percent,
  Pipe,
  Amp,
  Equal,
  Exclam,
  Tilde,
  Caret,

  LParen,
  RParen,
  LBrak,
  RBrak,
  LBrace,
  RBrace,

  Dot,
  Comma,
  Colon,
  Semicolon,

  PlusPlus,
  MinusMinus,
  AmpAmp,
  PipePipe,

  Lesser,
  LesserEqual,
  LesserLesser,
  Greater,
  GreaterEqual,
  GreaterGreater,

  PlusEqual,
  MinusEqual,
  AsteriskEqual,
  SlashEqual,
  PercentEqual,
  AmpEqual,
  PipeEqual,
  EqualEqual,
  ExclamEqual,

  GreaterGreaterEqual,
  LesserLesserEqual,

  Arrow,
  EqualBig,

  Numeric,
  String,
  Identifier,

  Null,
  True,
  False,
  Let,
  Type,
  Alias,
  Import,
  Export,
  Return,
  Struct,
  Enum,
  Alloc,
  If,
  EndIf,
  Loop,
  EndLoop,
  Lamb,
  Func,
  Vari,
  View,
  Job,
  Yield,
  Fiber,
  Serial,
  Parallel,
  Lock,
  Unlock,
  Swap,
  Flush,
  Shared,
  Break,
  Continue,
  Goto,
};

const std::unordered_map<std::string, TokenKind> Keywords = {
    {"null", TokenKind::Null},
    {"true", TokenKind::True},
    {"false", TokenKind::False},
    {"let", TokenKind::Let},
    {"type", TokenKind::Type},
    {"alias", TokenKind::Alias},
    {"import", TokenKind::Import},
    {"export", TokenKind::Export},
    {"return", TokenKind::Return},
    {"struct", TokenKind::Struct},
    {"enum", TokenKind::Enum},
    {"alloc", TokenKind::Alloc},
    {"if", TokenKind::If},
    {"endif", TokenKind::EndIf},
    {"loop", TokenKind::Loop},
    {"endloop", TokenKind::EndLoop},
    {"lamb", TokenKind::Lamb},
    {"func", TokenKind::Func},
    {"vari", TokenKind::Vari},
    {"view", TokenKind::View},
    {"job", TokenKind::Job},
    {"yield", TokenKind::Yield},
    {"fiber", TokenKind::Fiber},
    {"serial", TokenKind::Serial},
    {"parallel", TokenKind::Parallel},
    {"lock", TokenKind::Lock},
    {"unlock", TokenKind::Unlock},
    {"swap", TokenKind::Swap},
    {"flush", TokenKind::Flush},
    {"shared", TokenKind::Shared},
    {"break", TokenKind::Break},
    {"continue", TokenKind::Continue},
    {"goto", TokenKind::Goto},
};

struct PosInfo {
  uint32_t sline;
	uint32_t eline;
  uint32_t start;
  uint32_t end;
  uint32_t length;
  std::optional<std::string_view> filepath;
};

struct Token {
  TokenKind kind;
  PosInfo position;

  Token(TokenKind kind, uint32_t sline, uint32_t eline, uint32_t start, uint32_t end,
        uint32_t length, const std::string filepath)
      : kind(kind), position({.sline = sline,
															.eline = eline,
                              .start = start,
                              .end = end,
                              .length = length,
                              .filepath = filepath}) {}
};
}; // namespace Syntax
}; // namespace Z

#endif // Z_SYNTAX_TOKEN_HPP
