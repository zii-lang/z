#include <gtest/gtest.h>

#include <Z/IO.hpp>

using namespace Z::IO;

class FileSourceEmptyTest : public ::testing::Test {
protected:
  const char *testFileName = "temp_empty_file.txt";

  void SetUp() override {
    // Create an empty file
    std::ofstream out(testFileName, std::ios::binary);
  }

  void TearDown() override {
    // Remove the temporary file
    std::remove(testFileName);
  }
};

TEST_F(FileSourceEmptyTest, EmptyFileEOF) {
  FileSource fs(testFileName);

  // Size should be 0
  EXPECT_EQ(fs.size(), 0);

  // Position at start
  EXPECT_EQ(fs.pos(), 0);

  // EOF should be true immediately
  EXPECT_TRUE(fs.eof());

  // get() should return 0
  EXPECT_EQ(fs.get(), '\0');

  // peek() should return 0
  EXPECT_EQ(fs.peek(), '\0');

  // slice should return empty string
  EXPECT_EQ(fs.slice(0, 10), "");
}
