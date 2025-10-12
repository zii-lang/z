#include "Z/Compiler/Context.hpp"
#include "Z/IO/RandomAccess/MemoryReader.hpp"
#include <Z/Preprocessor.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace Z::PP {

TEST(PreprocessorTest, Sample) {
  const std::string source = "this source doesn't have any preprocessing.";
  IO::MemoryReader reader(source);
  Compiler::CompilerContext context;
  Preprocessor pp(reader, context);

  const auto &preprocessed = pp.process();
  const auto &mem = preprocessed.content.toReader();
  std::stringstream ss;
  while (!mem.eof()) {
		EXPECT_EQ(1, 2);
    ss.write(reinterpret_cast<const char *>(mem.peek()), 1);
    mem.advance(1);
  }
  // EXPECT_EQ(mem.peek(), 10);
}

} // namespace Z::PP
