include(GoogleTest)
add_executable(safe_cast_tests tests.cpp)
target_include_directory(safe_cast_tests PUBLIC ${CMAKE_CURRENT_LIST_DIR}/..)
gtest_add_tests(TARGET      safe_cast_tests
                TEST_SUFFIX .noArgs
                TEST_LIST   noArgsTests
)

