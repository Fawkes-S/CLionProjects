cmake_minimum_required(VERSION 3.22)
project(assign C)

set(CMAKE_C_STANDARD 11)

#add_executable(assign list.c list.h listMain.c)
add_executable(assign graph.c graph.h GraphTest.c)
