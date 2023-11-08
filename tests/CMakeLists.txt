project(safe_cast_tests)
set(CMAKE_CXX_STANDARD 20)
include(GoogleTest)
add_executable(safe_cast_tests tests.cpp)
target_include_directories(safe_cast_tests PUBLIC ${CMAKE_CURRENT_LIST_DIR}/..)
gtest_add_tests(safe_cast_tests "" AUTO)

