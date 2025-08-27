#ifndef Z_SYNTAX_FILE_SOURCE_HPP
#define Z_SYNTAX_FILE_SOURCE_HPP

#include <fstream>

#include "./input_source.hpp"

namespace Z {
namespace Syntax {
/**
 * Buffer of file as source.
 */
class FileSource : public InputSource {
  std::ifstream in;
  std::streampos file_size{0};
  const std::string path;

public:
  FileSource(const std::string &filepath);
  uint32_t peek() override;
  uint32_t peek(uint32_t pos) override;
  uint32_t get() override;
  bool eof() override;
  uint32_t get_pos() override;
  void set_pos(uint32_t pos) override;
  const std::string get_path() override;
  const std::string slice(uint32_t start, uint32_t length) override;
};

}; // namespace Syntax
}; // namespace Z

#endif
