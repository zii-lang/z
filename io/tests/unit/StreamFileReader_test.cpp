#include <gtest/gtest.h>

#include <Z/IO.hpp>

#include <fstream>

using namespace Z::IO;

TEST(StreamFileReaderTest, TemporaryFileRead) {
  // Create a temporary file
  const std::string tmpFile = "tmp_test_file.txt";
  {
    std::ofstream out(tmpFile, std::ios::binary);
    ASSERT_TRUE(out.is_open());
    out << "hello";
    out.close();
  }

  // Open file with StreamFileReader
  StreamFileReader reader(tmpFile);
  EXPECT_FALSE(reader.hasError());

  EXPECT_EQ(reader.pos(), 0u);
  EXPECT_FALSE(reader.eof());

  // Read first character
  EXPECT_EQ(reader.get(), 'h');
  EXPECT_EQ(reader.pos(), 1u);

  // Peek at next character without advancing
  EXPECT_EQ(reader.peek(), 'e');
  EXPECT_EQ(reader.pos(), 1u);

  // Read remaining characters
  EXPECT_EQ(reader.get(), 'e');
  EXPECT_EQ(reader.get(), 'l');
  EXPECT_EQ(reader.get(), 'l');
  EXPECT_EQ(reader.get(), 'o');

  EXPECT_EQ(reader.get(), 0);
  EXPECT_TRUE(reader.hasError());
  EXPECT_TRUE(reader.eof());

  // Clean up temporary file
  std::remove(tmpFile.c_str());
}

TEST(StreamFileReader, ConvertToRandomAccessAndRead) {
  const std::string tempFilePath = "test_stream_to_random.tmp";
  const std::string content = "Hello, Z!";

  // Step 1: Write temporary file
  {
    std::ofstream ofs(tempFilePath, std::ios::binary);
    ofs << content;
  }

  // Step 2: Create StreamFileReader
  StreamFileReader reader(tempFilePath);
  ASSERT_FALSE(reader.hasError(InputError::NullInput))
      << "StreamFileReader should open file successfully.";
  EXPECT_FALSE(reader.eof())
      << "StreamFileReader should not be at EOF initially.";

  // Step 3: Convert to RandomAccessReader
  auto randomReader = reader.toRandomAccess();
  ASSERT_NE(randomReader, nullptr)
      << "Conversion to RandomAccessReader failed.";

  // Step 4: Validate content through RandomAccessReader
  std::string readBack;
  while (!randomReader->eof()) {
    readBack.push_back(static_cast<char>(randomReader->get()));
  }

  EXPECT_EQ(readBack, content)
      << "RandomAccessReader should contain identical data.";

  // Step 5: Cleanup
  std::remove(tempFilePath.c_str());
}
