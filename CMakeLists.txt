cmake_minimum_required(VERSION 3.12)
project(Library LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -fconcepts -O3")
add_executable(Lib main.cpp BookEdition.cpp FictionEdition.cpp LearningEdition.cpp ScientificEdition.cpp Table.cpp)
