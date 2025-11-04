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

