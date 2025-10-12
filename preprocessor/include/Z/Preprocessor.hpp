#ifndef Z_PP_HPP
#define Z_PP_HPP

#include <Z/IO.hpp>
#include <cstddef>
#include <unordered_map>
#include <vector>

#include <Z/Compiler.hpp>
#include <Z/IO/InputReader.hpp>

namespace Z::PP {

struct RangeMapping {
  std::size_t preStart, rawStart;
};

struct PreprocessedSource {
  mutable IO::MemoryWriter content;
  mutable std::vector<RangeMapping> mappings;

  PreprocessedSource() : content(), mappings() {}
};

enum class DirectiveKind {
  If,
  Elif,
  Else,
  Define,
};

class Preprocessor {
private:
  const std::unordered_map<std::string, DirectiveKind> directives = {
      {"if", DirectiveKind::If},
      {"elif", DirectiveKind::Elif},
      {"else", DirectiveKind::Else},
      {"define", DirectiveKind::Define},
  };
  const IO::InputReader &_reader;
  const Compiler::CompilerContext _context;
  const PreprocessedSource _output;

  void skip_trivial() const noexcept;
  void handle_definition() const noexcept;

public:
  Preprocessor(const IO::InputReader &reader,
               const Compiler::CompilerContext &context);
  ~Preprocessor();

  const PreprocessedSource &process();
};
}; // namespace Z::PP

#endif
