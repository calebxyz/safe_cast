cmake_minimum_required(VERSION 3.18)

project(safe_cast_tests)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

include(GoogleTest)

enable_testing()

add_executable(safe_cast_tests tests.cpp)

target_link_libraries(safe_cast_tests GTest::gtest_main)

target_include_directories(safe_cast_tests PUBLIC ${CMAKE_CURRENT_LIST_DIR}/..)

gtest_add_tests(safe_cast_tests "" AUTO)

