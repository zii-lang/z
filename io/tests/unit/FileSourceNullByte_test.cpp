#include <gtest/gtest.h>

#include <Z/IO.hpp>

using namespace Z::IO;

class FileSourceNullByteTest : public ::testing::Test {
protected:
  const char *testFileName = "temp_nullbyte_file.txt";

  void SetUp() override {
    // Create a file containing a null byte and some characters
    std::ofstream out(testFileName, std::ios::binary);
    out << "A";
    out.put('\0'); // null byte
    out << "B";
  }

  void TearDown() override { std::remove(testFileName); }
};

TEST_F(FileSourceNullByteTest, NullByteIsNotEOF) {
  FileSource fs(testFileName);

  EXPECT_FALSE(fs.eof());   // not at EOF yet
  EXPECT_EQ(fs.get(), 'A'); // first character
  EXPECT_FALSE(fs.eof());   // still not EOF

  EXPECT_EQ(fs.get(), '\0'); // read null byte
  EXPECT_FALSE(fs.eof());    // still not EOF

  EXPECT_EQ(fs.get(), 'B'); // last character
  EXPECT_TRUE(fs.eof());    // now at EOF

  // peek at EOF returns '\0'
  EXPECT_EQ(fs.peek(), '\0');
}
