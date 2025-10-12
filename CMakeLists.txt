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

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ZConfig.hpp.in
               ${CMAKE_CURRENT_BINARY_DIR}/include/Z/ZConfig.hpp @ONLY)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

set(PROJECT_LIST "compiler" "io" "preprocessor" "syntax")

foreach(project ${PROJECT_LIST})
  add_subdirectory(${project})
endforeach()
