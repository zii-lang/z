project(
  ZIO
  VERSION "1.0.0"
  LANGUAGES CXX)

# Get header files as build dependencies.
file(GLOB_RECURSE ZIO_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/Z/IO.hpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/include/Z/IO/**.hpp")
# All sources inside src directory.
file(GLOB_RECURSE ZIO_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp")

# Source header directory.
set(ZIO_HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/Z/IO")
# Build header directory.
set(ZIO_BUILD_HEADERS_DIR "${CMAKE_CURRENT_BINARY_DIR}/include/Z/IO")

add_custom_target(
  copy_io_headers ALL
  COMMAND ${CMAKE_COMMAND} -E make_directory ${ZIO_BINARY_DIR}
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${ZIO_SOURCE_DIR} ${ZIO_BINARY_DIR}
  DEPENDS ${ZIO_HEADERS})

add_library(ZIO "${ZIO_SOURCES}")
add_dependencies(ZIO copy_io_headers)
target_include_directories(
  ZIO PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
             $<INSTALL_INTERFACE:include>)

# Install the library
install(
  TARGETS ZIO
  EXPORT ZIOTargets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

# Install the public headers
install(DIRECTORY include DESTINATION include)

if(ENABLE_TESTS)
  add_subdirectory(tests)
endif()
