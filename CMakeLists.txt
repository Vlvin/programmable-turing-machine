cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(TuringMachine)

set(CMAKE_CXX_STANDARD 23)

add_executable(${CMAKE_PROJECT_NAME} ./main.cpp ./src/turing_machine.cpp)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ./src)
