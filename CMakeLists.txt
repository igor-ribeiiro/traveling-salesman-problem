cmake_minimum_required(VERSION 3.9)
project(CES-12)

set(CMAKE_CXX_STANDARD 11)

add_executable(CES-12 TSP.cpp)
add_executable(CREATE_GRAPH create_graph.cpp)