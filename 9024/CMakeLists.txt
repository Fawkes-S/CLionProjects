cmake_minimum_required(VERSION 3.22)
project(9024 C)

set(CMAKE_C_STANDARD 11)

add_executable(9024 IntStack.h StackTester.c Stack.c Stack.h binary.c IntQueue.h IntQueue.c testQueue.c w2/split.c)
