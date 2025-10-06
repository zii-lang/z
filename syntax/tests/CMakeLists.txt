add_executable(test_ZSyntax test1.cpp)

target_link_libraries(test_ZSyntax PRIVATE ZSyntax GTest::gtest
                                           GTest::gtest_main)

add_test(NAME SyntaxTests COMMAND test_ZSyntax)
