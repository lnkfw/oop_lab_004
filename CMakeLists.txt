cmake_minimum_required(VERSION 3.10)

project(lab_004
    VERSION 1.0.0
    DESCRIPTION "lab_004"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(lab_004 main.cpp)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(lab_04_tests tests/test_figures.cpp)
target_link_libraries(lab_04_tests PRIVATE gtest_main)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(lab_04_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

include(GoogleTest)
gtest_discover_tests(lab_04_tests)
