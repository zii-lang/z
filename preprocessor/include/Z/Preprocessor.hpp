#ifndef Z_PP_HPP
#define Z_PP_HPP

#include <cstddef>
#include <unordered_map>
#include <vector>

#include <Z/Compiler.hpp>
#include <Z/IO.hpp>

namespace Z::PP {

/**
 * A map where raw position is actually the reset position in another source.
 */
struct ResetMap {
  std::size_t raw, reset;
  ResetMap(std::size_t raw, std::size_t reset) {}
};

struct PreprocessedSource {
  mutable IO::MemoryWriter content;
  mutable std::vector<ResetMap> mappings;
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

  const PreprocessedSource &process() const noexcept;
};
}; // namespace Z::PP

#endif
