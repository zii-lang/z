#include <gtest/gtest.h>

#include <Z/IO.hpp>

using namespace Z::IO;

TEST(MemoryReaderTest, GetAndPos) {
  MemoryReader reader("hello");

  EXPECT_EQ(reader.pos(), 0u);
  EXPECT_EQ(reader.get(), 'h');
  EXPECT_EQ(reader.get(), 'e');
  EXPECT_EQ(reader.pos(), 2u);
}

TEST(MemoryReaderTest, PeekWithoutAdvancing) {
  MemoryReader reader("abc");

  EXPECT_EQ(reader.peek(), 'a');
  EXPECT_EQ(reader.peek(1), 'b');
  EXPECT_EQ(reader.peek(2), 'c');
  EXPECT_EQ(reader.pos(), 0u); // pos does not advance
}

TEST(MemoryReaderTest, GetAndEof) {
  MemoryReader reader("x");

  EXPECT_FALSE(reader.eof());
  EXPECT_EQ(reader.get(), 'x');
  EXPECT_TRUE(reader.eof());
}

TEST(MemoryReaderTest, AtFunction) {
  MemoryReader reader("data");

  EXPECT_EQ(reader.at(0), 'd');
  EXPECT_EQ(reader.at(2), 't');
  reader.at(99);
  EXPECT_TRUE(reader.hasError());
}

TEST(MemoryReaderTest, SeekWithinBounds) {
  MemoryReader reader("world");

  reader.seek(3);
  EXPECT_EQ(reader.pos(), 3u);
  EXPECT_EQ(reader.get(), 'l');
}

TEST(MemoryReaderTest, SeekBeyondBoundsClamped) {
  MemoryReader reader("123");

  reader.seek(100);
  EXPECT_TRUE(reader.eof());
  EXPECT_EQ(reader.pos(), 3u);
}

TEST(MemoryReaderTest, PeekBeyondEndThrows) {
  MemoryReader reader("a");

  EXPECT_EQ(reader.peek(1), 0);
  EXPECT_TRUE(reader.hasError());
}

TEST(MemoryReaderTest, GetBeyondEndThrows) {
  MemoryReader reader("x");

  EXPECT_EQ(reader.get(), 'x');
  EXPECT_EQ(reader.get(), 0);
  EXPECT_TRUE(reader.hasError());
}
