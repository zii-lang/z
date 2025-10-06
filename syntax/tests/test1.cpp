#include "Z/Syntax/file_source.hpp"
#include <Z/Syntax/FileSource>

#include <gtest/gtest.h>

TEST(Input, Basic) {
	Z::Syntax::FileSource source("test_file");
}
