project(
  ZSyntax
  VERSION "1.0.0"
  LANGUAGES CXX)

# Get header files as build dependencies.
file(GLOB_RECURSE ZSYNTAX_HEADERS
     "${CMAKE_CURRENT_SOURCE_DIR}/include/Z/Syntax/*")
# All sources inside src directory.
file(GLOB_RECURSE ZSYNTAX_SOURCES src/file_source.cpp
)# "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Source header directory.
set(ZSYNTAX_HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/Z/Syntax")
# Build header directory.
set(ZSYNTAX_BUILD_HEADERS_DIR "${CMAKE_CURRENT_BINARY_DIR}/include/Z/Syntax")

add_custom_target(
  copy_syntax_headers ALL
  COMMAND ${CMAKE_COMMAND} -E make_directory ${ZSyntax_BINARY_DIR}
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${ZSyntax_SOURCE_DIR}
          ${ZSyntax_BINARY_DIR}
  DEPENDS ${ZSYNTAX_HEADERS})

add_library(ZSyntax "${ZSYNTAX_SOURCES}")
add_dependencies(ZSyntax copy_syntax_headers)
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

if(ENABLE_TESTS)
  add_subdirectory(tests)
endif()
