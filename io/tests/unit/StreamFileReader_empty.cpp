#include <Z/IO.hpp>
#include <cstdio>
#include <fstream>
#include <gtest/gtest.h>

using namespace Z::IO;

class StreamFileReaderEmptyTest : public ::testing::Test {
protected:
  std::string tempFilePath;

  void SetUp() override {
    // Create a temporary empty file
    tempFilePath = "test_empty_file.tmp";
    std::ofstream ofs(tempFilePath, std::ios::binary);
    ofs.close();
  }

  void TearDown() override { std::remove(tempFilePath.c_str()); }
};

TEST_F(StreamFileReaderEmptyTest, EmptyFileReportsEOF) {
  StreamFileReader reader(tempFilePath);

  // File should exist and be open
  EXPECT_FALSE(reader.hasError(InputError::NullInput))
      << "File should open successfully.";

  // Immediately at EOF for empty file
  EXPECT_TRUE(reader.eof()) << "Empty file should be at EOF immediately.";

  // get() should set EOFReached
  uint8_t value = reader.get();
  EXPECT_EQ(value, 0);
  EXPECT_TRUE(reader.hasError(InputError::EOFReached))
      << "Reading from empty file should trigger EOFReached.";
}

TEST_F(StreamFileReaderEmptyTest, EmptyFileToRandomAccessIsEmpty) {
  StreamFileReader reader(tempFilePath);
  auto memReader = reader.toRandomAccess();
  ASSERT_NE(memReader, nullptr);

  EXPECT_TRUE(memReader->eof())
      << "Converted memory reader should also be at EOF.";
}
