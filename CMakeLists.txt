cmake_minimum_required(VERSION 3.6)
project(test_boost_spirit)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pedantic -Wall")
include_directories("C:/libs/boost_1_62_0")
set(SOURCE_FILES main.cpp front_end/Boogie/Parser.cpp)
add_executable(test_boost_spirit ${SOURCE_FILES})