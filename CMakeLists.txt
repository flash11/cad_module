cmake_minimum_required(VERSION 3.16)
project(CadProject CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(core src/point_line_projection.cpp)

target_include_directories(core PUBLIC include)

find_package(GTest CONFIG REQUIRED)

add_executable(done_tests tests/test_newton.cpp)

target_link_libraries(done_tests PRIVATE core GTest::gtest_main)

enable_testing()

include(GoogleTest)
gtest_discover_tests(done_tests)