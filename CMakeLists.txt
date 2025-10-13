cmake_minimum_required(VERSION 3.20.0)

project(
  Z
  VERSION "1.0.0"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_TESTS "Enable tests for modules" OFF)

if(ENABLE_TESTS)
  # Try to find system-installed GTest first
  find_package(GTest QUIET)

  if(NOT GTest_FOUND)
    message(STATUS "System GTest not found, falling back to FetchContent")

    include(FetchContent)
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/refs/tags/release-1.17.0.zip
    )
    FetchContent_MakeAvailable(googletest)
  endif()
  include(GoogleTest)
  enable_testing()
endif()

set(SRC_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(BUILD_INCLUDE_DIR "${CMAKE_BINARY_DIR}/include/Z")
file(MAKE_DIRECTORY ${BUILD_INCLUDE_DIR})
file(
  GLOB_RECURSE HEADER_FILES
  RELATIVE ${SRC_INCLUDE_DIR}
  "${SRC_INCLUDE_DIR}/*.hpp")

foreach(file ${HEADER_FILES})
  # Make sure the destination subdirectory exists
  get_filename_component(dir "${file}" DIRECTORY)
  file(MAKE_DIRECTORY "${BUILD_INCLUDE_DIR}/${dir}")

  # Add custom command to copy file
  add_custom_command(
    OUTPUT "${BUILD_INCLUDE_DIR}/${file}"
    COMMAND ${CMAKE_COMMAND} -E copy "${SRC_INCLUDE_DIR}/${file}"
            "${BUILD_INCLUDE_DIR}/${file}"
    DEPENDS "${SRC_INCLUDE_DIR}/${file}"
    COMMENT "Copying ${file} to build include directory")
  list(APPEND COPIED_FILES "${BUILD_INCLUDE_DIR}/${file}")
endforeach()

add_custom_target(copy_includes ALL DEPENDS ${COPIED_FILES})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/ZConfig.hpp.in
               ${CMAKE_CURRENT_BINARY_DIR}/include/Z/ZConfig.hpp @ONLY)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

set(PROJECT_LIST "compiler" "io" "preprocessor" "syntax" "internal_build")

foreach(project ${PROJECT_LIST})
  add_subdirectory(${project})
endforeach()
