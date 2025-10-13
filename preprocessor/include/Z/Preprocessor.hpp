#ifndef Z_PP_HPP
#define Z_PP_HPP

#include <cstddef>
#include <unordered_map>
#include <vector>

#include <Z/Compiler.hpp>
#include <Z/IO.hpp>

namespace Z::PP {

struct RangeMapping {
  std::size_t startPre, startRaw, endPre, endRaw;
  RangeMapping(std::size_t startPre, std::size_t startRaw, std::size_t endPre,
               std::size_t endRaw)
      : startPre(startPre), startRaw(startRaw), endPre(endPre), endRaw(endRaw) {
  }
};

struct PreprocessedSource {
  mutable IO::MemoryWriter content;
  mutable std::vector<RangeMapping> mappings;
  mutable bool proccessed = false;

  PreprocessedSource() : content(), mappings() {}
};

enum class DirectiveKind {
  If,
  Elif,
  Else,
  Endif,
  Define,
};

enum class PreprocessorState {
  None,
  If,
  Else,
  End,
  Comment,
};

class Preprocessor {
private:
  const std::unordered_map<std::string, DirectiveKind> directives = {
      {"if", DirectiveKind::If},       {"elif", DirectiveKind::Elif},
      {"else", DirectiveKind::Else},   {"define", DirectiveKind::Define},
      {"endif", DirectiveKind::Endif},
  };
  const IO::InputReader &_reader;
  const Compiler::CompilerContext _context;
  const PreprocessedSource _output;
  PreprocessorState state = PreprocessorState::None;

  void skip_trivial() const noexcept;
  void handle_definition(const std::string) const noexcept;

public:
  Preprocessor(const IO::InputReader &reader,
               const Compiler::CompilerContext &context);
  ~Preprocessor();

  const PreprocessedSource &process();
};
}; // namespace Z::PP

#endif
