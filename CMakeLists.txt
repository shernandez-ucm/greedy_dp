cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project (heap_sort)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable (custom_sort src/01_customsort.cpp)
add_executable (heap_sort src/02_heapsort.cpp)
add_executable (knapsack_heap src/03_heapsort_knapsack.cpp)
