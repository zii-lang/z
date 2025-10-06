#include <Z/IO.hpp>
#include <gtest/gtest.h>

using namespace Z::IO;

class FileSourceLargeFileTest : public ::testing::Test {
protected:
  const char *testFileName = "temp_large_file.txt";
  const size_t fileSize = 1 << 20; // 1 MB for testing; adjust as needed

  void SetUp() override {
    std::ofstream out(testFileName, std::ios::binary);
    for (size_t i = 0; i < fileSize; ++i) {
      char c = static_cast<char>('A' + (i % 26)); // repeating alphabet
      out.put(c);
    }
  }

  void TearDown() override { std::remove(testFileName); }
};

TEST_F(FileSourceLargeFileTest, SizeAndSequentialRead) {
  FileSource fs(testFileName);

  EXPECT_EQ(fs.size(), fileSize);

  size_t readCount = 0;
  while (!fs.eof()) {
    fs.get();
    ++readCount;
  }

  // After reading all bytes, position should match file size
  EXPECT_EQ(readCount, fileSize);
  EXPECT_EQ(fs.pos(), fileSize);
  EXPECT_TRUE(fs.eof());
}

TEST_F(FileSourceLargeFileTest, SliceFromMiddle) {
  FileSource fs(testFileName);
  const size_t start = 1000;
  const size_t len = 50;
  std::string slice = fs.slice(start, len);

  EXPECT_EQ(slice.size(), len);

  // Verify predictable pattern
  for (size_t i = 0; i < len; ++i) {
    char expected = static_cast<char>('A' + ((start + i) % 26));
    EXPECT_EQ(slice[i], expected);
  }
}

TEST_F(FileSourceLargeFileTest, PeekDoesNotAdvancePosition) {
  FileSource fs(testFileName);

  uint32_t first = fs.peek();
  EXPECT_EQ(first, 'A');
  EXPECT_EQ(fs.pos(), 0); // position unchanged

  uint32_t second = fs.get();
  EXPECT_EQ(second, 'A');
  EXPECT_EQ(fs.pos(), 1);
}

TEST_F(FileSourceLargeFileTest, GetLastCharacterAndCheckEOF) {
  FileSource fs(testFileName);

  // Seek to one byte before end
  fs.seek(fileSize - 1, SeekKind::Start);

  EXPECT_FALSE(fs.eof());

  // Get the final byte
  uint32_t last = fs.get();
  char expected = static_cast<char>('A' + ((fileSize - 1) % 26));
  EXPECT_EQ(last, expected);

  // Now EOF should be true
  EXPECT_TRUE(fs.eof());

  // Subsequent get() should return '\0'
  EXPECT_EQ(fs.get(), '\0');
}
