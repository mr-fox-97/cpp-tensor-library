cmake_minimum_required(VERSION 3.20)
project(Merlot)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_library(Merlot INTERFACE)
target_include_directories(Merlot INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Tests tests/test_memory.cpp)
target_link_libraries(Tests ${GTEST_BOTH_LIBRARIES} Merlot)

set_target_properties(Tests PROPERTIES CXX_STANDARD 20)