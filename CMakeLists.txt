cmake_minimum_required(VERSION 3.14)
project(heaps)

set(CMAKE_CXX_STANDARD 17)

add_executable(heaps main.cpp src/iheap.h include/binomial_heap.h src/heap_exceptions.h src/stl_heap.h tests/tester.h tests/assertions.h)