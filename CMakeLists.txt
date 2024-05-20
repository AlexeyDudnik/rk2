cmake_minimum_required(VERSION 3.10)

# Project name
project(chain-of-responsibility)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
add_executable(chain-of-responsibility src/ChainOfResponsibility.cpp)

# Enable testing
enable_testing()
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(chain-of-responsibilityTest tests/test.cpp)
target_link_libraries(chain-of-responsibilityTest ${GTEST_LIBRARIES} pthread)

add_test(NAME chain-of-responsibilityTest COMMAND chain-of-responsibilityTest)
