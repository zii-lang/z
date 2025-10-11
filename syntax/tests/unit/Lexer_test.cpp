#include <Z/IO.hpp>
#include <Z/Syntax.hpp>
#include <gtest/gtest.h>

using namespace Z;

TEST(Lexer, LParenWithComment) {
  IO::MemoryReader reader("// Hello Comment\n (");
  Syntax::Lexer lexer(reader);
  EXPECT_EQ(lexer.get().kind, Syntax::TokenKind::LParen);
}
