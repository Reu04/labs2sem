cmake_minimum_required(VERSION 3.23)

project(cmake_testapp)

set(CMAKE_CXX_STANDARD 17)

add_executable(cmake_testapp main.cpp DynamicArray.cpp LinkedList.cpp ArraySequence.cpp LinkedListSequence.cpp UserInterface.cpp)