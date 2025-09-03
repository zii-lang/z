#ifndef Z_SYNTAX_FILE_SOURCE_HPP
#define Z_SYNTAX_FILE_SOURCE_HPP

#include <fstream>

#include <Z/Syntax/InputSource>

namespace Z {
namespace Syntax {
/**
 * Buffer of file as source.
 */
class FileSource : public InputSource {
  std::ifstream in;
  std::streampos file_size{0};
  const std::string path;
  uint32_t line = 1;
	uint32_t length = 0;

public:
  FileSource(const std::string &filepath);

  uint32_t peek() override;
  uint32_t peek(uint32_t pos) override;
  uint32_t get() override;

  bool eof() override;

	uint32_t get_pos() override;
  void set_pos(uint32_t pos) override;
  void inc_pos() override;
  uint32_t get_line() override;
  void inc_line() override;
	uint32_t get_length() override;
	void clear() override;

  const std::string get_path() override;
  const std::string slice(uint32_t start, uint32_t length) override;
};

}; // namespace Syntax
}; // namespace Z

#endif
