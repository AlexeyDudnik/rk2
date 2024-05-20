# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)

# Название проекта
project(chain-of-responsibility)

# Установить стандарт C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавить исходные файлы
add_executable(chain-of-responsibility src/ChainOfResponsibility.cpp)

# Добавить тесты
enable_testing()
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(chain-of-responsibilityTest tests/test.cpp)
target_link_libraries(chain-of-responsibilityTest ${GTEST_LIBRARIES} pthread)

add_test(NAME chain-of-responsibilityTest COMMAND chain-of-responsibilityTest)
