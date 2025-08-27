project(
  ZSyntax
  VERSION "1.0.0"
  LANGUAGES CXX)

add_library(ZSyntax src/lexer.cpp src/string_source.cpp src/file_source.cpp)

target_include_directories(
  ZSyntax PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                 $<INSTALL_INTERFACE:include>)

# Install the library
install(
  TARGETS ZSyntax
  EXPORT ZSyntaxTargets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

# Install the public headers
install(DIRECTORY include DESTINATION include)
