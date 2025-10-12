# -----------------------
# Unit Tests
# -----------------------
file(GLOB UNIT_TEST_SOURCES "unit/*.cpp")

if(UNIT_TEST_SOURCES)
  add_executable(pp_unit_tests ${UNIT_TEST_SOURCES})
  target_link_libraries(
    pp_unit_tests PRIVATE ZIO ZPreprocessor GTest::gtest GTest::gtest_main)

  add_test(NAME pp_unit_tests COMMAND pp_unit_tests)
	gtest_discover_tests(pp_unit_tests)
endif()
