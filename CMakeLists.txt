cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project (heap_sort)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable (custom_sort src/01_customsort.cpp)
add_executable (heap_sort src/02_heapsort.cpp)
add_executable (knapsack_heap src/03_heapsort_knapsack_solution.cpp)
add_executable (knapsack_dp src/04_dp_knapsack_solution.cpp)
add_executable (knapsack_test src/05_random_knapsack.cpp)
add_executable (shortest_path src/graph.hpp src/06_shortest_path.cpp)
add_executable (shortest_path_negative_weight src/graph.hpp src/06_shortest_path_negative_weight.cpp)


