cmake_minimum_required(VERSION 3.22)
project(code)

set(CMAKE_CXX_STANDARD 16)

add_executable(code main.cpp Book.h Account.h  diary-condition.h error.h linklist.h token_scanner.h)
