cmake_minimum_required(VERSION 3.12)
project(Library LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -fconcepts")
add_executable(Lib List.cpp main.cpp BookEdition.cpp FictionEdition.cpp LearningEdition.cpp ScientificEdition.cpp Table.cpp)
add_executable(Dialog List.cpp dialogMain.cpp BookEdition.cpp FictionEdition.cpp LearningEdition.cpp ScientificEdition.cpp Table.cpp)
add_executable(TestList List.cpp Test.cpp BookEdition.cpp  FictionEdition.cpp)