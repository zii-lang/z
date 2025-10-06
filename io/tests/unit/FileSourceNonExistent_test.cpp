#include <Z/IO.hpp>
#include <gtest/gtest.h>

using namespace Z::IO;

TEST(FileSourceNonExistentTest, ThrowsOnMissingFile) {
  const std::string missingFile = "this_file_should_not_exist.txt";

  // Expect constructor to throw std::runtime_error
  EXPECT_THROW({ FileSource fs(missingFile); }, std::runtime_error);
}
