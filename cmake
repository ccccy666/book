cmake_minimum_required(VERSION 3.22)
project(code)

set(CMAKE_CXX_STANDARD 17)

add_executable(code main.cpp Book.h Account.h  diary.h error.h token_scanner.h)
