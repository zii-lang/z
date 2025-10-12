# -----------------------
# Unit Tests
# -----------------------
file(GLOB UNIT_TEST_SOURCES "unit/*.cpp")

if(UNIT_TEST_SOURCES)
  add_executable(syntax_unit_tests ${UNIT_TEST_SOURCES})
  target_link_libraries(syntax_unit_tests PRIVATE ZIO ZPreprocessor GTest::gtest
                                              GTest::gtest_main)

  add_test(NAME syntax_unit_tests COMMAND syntax_unit_tests)
  gtest_discover_tests(syntax_unit_tests)
endif()
