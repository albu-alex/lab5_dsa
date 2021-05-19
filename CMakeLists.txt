cmake_minimum_required(VERSION 3.19)
project(lab5_dsa)

set(CMAKE_CXX_STANDARD 14)

include_directories("Header Files")

add_executable(lab5_dsa
        "Header Files/ExtendedTest.h"
        "Header Files/ShortTest.h"
        "Header Files/SMMIterator.h"
        "Header Files/SortedMultiMap.h"
        "Source Files/App.cpp"
        "Source Files/ExtendedTest.cpp"
        "Source Files/ShortTest.cpp"
        "Source Files/SMMIterator.cpp"
        "Source Files/SortedMultiMap.cpp")
