#include "Z/Compiler/Context.hpp"
#include "Z/IO/RandomAccess/MemoryReader.hpp"
#include <Z/Preprocessor.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace Z::PP {

TEST(PreprocessorTest, NoChangePreprocessing) {
  const std::string source = "this source doesn't have any preprocessing.";
  IO::MemoryReader reader(source);
  Compiler::CompilerContext context;
  Preprocessor pp(reader, context);

  const auto &preprocessed = pp.process();
  const auto &mem = preprocessed.content.toReader();
  std::stringstream ss;
  uint8_t c;
  while (!mem.eof()) {
    c = mem.peek();
    ss.write(reinterpret_cast<const char *>(&c), 1);
    mem.advance(1);
  }
	EXPECT_EQ(source, ss.str());
}

TEST(PreprocessorTest, LineAndSingleDefine) {
  const std::string source = "#define TEST 1\nsome random text.";
  IO::MemoryReader reader(source);
  Compiler::CompilerContext context;
  Preprocessor pp(reader, context);

  const auto &preprocessed = pp.process();
  const auto &mem = preprocessed.content.toReader();
  std::stringstream ss;
  uint8_t c;
  while (!mem.eof()) {
    c = mem.peek();
    ss.write(reinterpret_cast<const char *>(&c), 1);
    mem.advance(1);
  }
	EXPECT_EQ("some random text.", ss.str());
}

} // namespace Z::PP
