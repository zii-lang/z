#include <cstdio>
#include <fstream>
#include <gtest/gtest.h>
#include <string>

#include <Z/IO.hpp>

using namespace Z::IO;

class FileSourceTest : public ::testing::Test {
protected:
  const char *testFileName = "temp_test_file.txt";

  void SetUp() override {
    // Create a temporary file with known content
    std::ofstream out(testFileName, std::ios::binary);
    out << "Hello, Z!\nLine2";
  }

  void TearDown() override {
    // Remove temporary file
    std::remove(testFileName);
  }
};

// --------------------
// Basic tests
// --------------------
TEST_F(FileSourceTest, BasicFileOpening) {
  EXPECT_NO_THROW({ FileSource fs(testFileName); });
}

TEST_F(FileSourceTest, SizeAndPos) {
  FileSource fs(testFileName);
  EXPECT_EQ(fs.size(), 15); // "Hello, Z!\nLine2" is 15 bytes
  EXPECT_EQ(fs.pos(), 0);   // Initial position at start
}

TEST_F(FileSourceTest, PeekAndGet) {
  FileSource fs(testFileName);

  // peek without advancing
  EXPECT_EQ(fs.peek(), 'H');
  EXPECT_EQ(fs.pos(), 0);

  // get advances
  uint32_t ch = fs.get();
  EXPECT_EQ(ch, 'H');
  EXPECT_EQ(fs.pos(), 1);

  // peek with n > 0
  EXPECT_EQ(fs.peek(2), 'l'); // lookahead 2 chars from current
  EXPECT_EQ(fs.pos(), 1);     // position shouldn't change
}

TEST_F(FileSourceTest, SeekAndPos) {
  FileSource fs(testFileName);

  fs.seekTo(9); // move to 9th byte
  EXPECT_EQ(fs.pos(), 9);
  EXPECT_EQ(fs.get(), '\n'); // should read newline at pos 9
}

TEST_F(FileSourceTest, EofBehavior) {
  FileSource fs(testFileName);

  // Read entire file
  while (!fs.eof())
    fs.get();
  EXPECT_TRUE(fs.eof());

  // get at EOF returns 0
  EXPECT_EQ(fs.get(), '\0');
}
