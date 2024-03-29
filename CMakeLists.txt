cmake_minimum_required(VERSION 3.12)
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif ()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif ()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif ()

# Now simply link against gtest or gtest_main as needed. Eg
set(CMAKE_CXX_STANDARD 17)

add_executable(heaps tests/main.cpp src/IHeap.h include/BinomialHeap.h src/HeapExceptions.h src/StlHeap.h include/LeftistHeap.h src/BaseHeap.h src/nodes/BaseNode.h src/nodes/LeftistNode.h src/nodes/SkewNode.h include/SkewHeap.h src/nodes/BinomialNode.h tests/HeapTest.h)
target_link_libraries(heaps gtest_main)

enable_testing()
add_test(NAME BinomialHeapTest COMMAND heaps)
add_test(NAME StlHeapTest COMMAND heaps)
add_test(NAME LeftistHeapTest COMMAND heaps)
add_test(NAME SkewHeapTest COMMAND heaps)