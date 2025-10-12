#include <Z/IO.hpp>
#include <Z/Syntax.hpp>
#include <gtest/gtest.h>

using namespace Z;

// TEST(Lexer, SingleTokenWithComment) {
//  IO::MemoryReader reader("// Hello Comment\n (");
//  Syntax::Lexer lexer(reader);
//  EXPECT_EQ(lexer.get().kind, Syntax::TokenKind::LParen);

//  IO::MemoryReader reader2(
//      "/* this is a comment \r\n another line ( of comment \n*/(");
//  Syntax::Lexer lexer2(reader2);
//  EXPECT_EQ(lexer2.get().kind, Syntax::TokenKind::LParen);
// }
