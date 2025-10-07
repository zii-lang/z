# -----------------------
# Unit Tests
# -----------------------
file(GLOB UNIT_TEST_SOURCES "unit/*.cpp")

if(UNIT_TEST_SOURCES)
  add_executable(io_unit_tests ${UNIT_TEST_SOURCES})
  target_link_libraries(io_unit_tests PRIVATE ZIO GTest::gtest
                                              GTest::gtest_main)

	add_test(NAME io_unit_tests COMMAND io_unit_tests)
	gtest_discover_tests(io_unit_tests)
endif()

# -----------------------
# Integration Tests
# -----------------------
file(GLOB INTEGRATION_TEST_SOURCES "integration/*.cpp")

if(INTEGRATION_TEST_SOURCES)
  add_executable(io_integration_tests ${INTEGRATION_TEST_SOURCES})
  target_link_libraries(io_integration_tests PRIVATE ZIO GTest::gtest
                                                     GTest::gtest_main)

  # Register each integration test with CTest
  foreach(test_file ${INTEGRATION_TEST_SOURCES})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_test(NAME ${test_name} COMMAND io_integration_tests)
  endforeach()
endif()
