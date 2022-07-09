cmake_minimum_required(VERSION 3.22)
project(untitled1 C)

set(CMAKE_C_STANDARD 11)

#add_executable(untitled1 graphAnalyser.c Graph.c)
#add_executable(untitled1 DFS.c)
#add_executable(untitled1 pack/Graph.c pack/Graph.h depthfindsearch.c)
#add_executable(untitled1 cycleCheck.c Graph.c)
#add_executable(untitled1 Warshall.c)
#add_executable(untitled1 WGraph.c WGraph.h)
#add_executable(untitled1 pack/WGraph.c pack/WGraph.h popularityRank.c)
add_executable(untitled1 pack/WGraph.c pack/WGraph.h pack/PQueue.h pack/PQueue.c dijkstra.c)
#add_executable(untitled1 pack/WGraph.c pack/WGraph.h pack/PQueue.h pack/PQueue.c Warshall.c)