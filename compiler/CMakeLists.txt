project(
  ZCompiler
  VERSION "1.0.0"
  LANGUAGES CXX)

# Get header files as build dependencies.
file(GLOB_RECURSE ZCOMPILER_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/Z/Compiler.hpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/include/Z/Compiler/**.hpp")

# All sources inside src directory.
file(GLOB_RECURSE ZCOMPILER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Source header directory.
set(ZCOMPILER_HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/Z/Compiler")
# Build header directory.
set(ZCOMPILER_BUILD_HEADERS_DIR "${CMAKE_CURRENT_BINARY_DIR}/include/Z/Compiler")

add_custom_target(
  copy_compiler_headers ALL
  COMMAND ${CMAKE_COMMAND} -E make_directory ${ZCompiler_BINARY_DIR}
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${ZCompiler_SOURCE_DIR}
          ${ZCompiler_BINARY_DIR}
  DEPENDS ${ZCOMPILER_HEADERS})

add_library(ZCompiler "${ZCOMPILER_SOURCES}")
add_dependencies(ZCompiler copy_compiler_headers)
target_include_directories(
  ZCompiler PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                       $<INSTALL_INTERFACE:include>)
target_link_libraries(ZCompiler PUBLIC ZIO)

# Install the library
install(
  TARGETS ZCompiler
  EXPORT ZCompilerTargets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

# Install the public headers
install(DIRECTORY include DESTINATION include)

if(ENABLE_TESTS)
  add_subdirectory(tests)
endif()
