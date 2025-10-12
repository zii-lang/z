project(
  ZPreprocessor
  VERSION "1.0.0"
  LANGUAGES CXX)

# Get header files as build dependencies.
file(GLOB_RECURSE ZPP_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/Z/PP.hpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/include/Z/PP/**.hpp")

# All sources inside src directory.
file(GLOB_RECURSE ZPP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Source header directory.
set(ZPP_HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/Z/PP")
# Build header directory.
set(ZPP_BUILD_HEADERS_DIR "${CMAKE_CURRENT_BINARY_DIR}/include/Z/PP")

add_custom_target(
  copy_preprocessor_headers ALL
  COMMAND ${CMAKE_COMMAND} -E make_directory ${ZPreprocessor_BINARY_DIR}
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${ZPreprocessor_SOURCE_DIR}
          ${ZPreprocessor_BINARY_DIR}
  DEPENDS ${ZPP_HEADERS})

add_library(ZPreprocessor "${ZPP_SOURCES}")
add_dependencies(ZPreprocessor copy_preprocessor_headers)
target_include_directories(
  ZPreprocessor PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                       $<INSTALL_INTERFACE:include>)
target_link_libraries(ZPreprocessor PUBLIC ZIO ZCompiler)

# Install the library
install(
  TARGETS ZPreprocessor
  EXPORT ZPreprocessorTargets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

# Install the public headers
install(DIRECTORY include DESTINATION include)

if(ENABLE_TESTS)
  add_subdirectory(tests)
endif()
