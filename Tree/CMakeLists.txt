cmake_minimum_required(VERSION 3.22)
project(Tree C)

set(CMAKE_C_STANDARD 11)

#add_executable(Tree BSTree.c BSTree.h treeLab.c)
add_executable(Tree W8/BST.c W8/BST.h W8/queue.c W8/queue.h W8/TreeLab.c)