cmake_minimum_required(VERSION 3.22)
project(week23)

set(CMAKE_CXX_STANDARD 11)

add_executable(week23 main.c SList.h SList.c palindrome.c)
