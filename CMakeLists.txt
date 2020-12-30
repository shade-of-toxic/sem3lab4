cmake_minimum_required(VERSION 3.12)
project(Library LANGUAGES CXX)

# Include(FetchContent)

# FetchContent_Declare(
#   Catch2
#   GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#   GIT_TAG        v2.13.1)

# #FetchContent_MakeAvailable(Catch2)
# FetchContent_GetProperties(Catch2) #mispelled name in original post
# if(NOT Catch2_POPULATED)
#   FetchContent_Populate(Catch2)
#   message(STATUS "Catch source dir: ${catch2_SOURCE_DIR}")
#   message(STATUS "Catch binary dir: ${catch2_BINARY_DIR}")
#   add_subdirectory(${catch2_SOURCE_DIR} ${catch2_BINARY_DIR}) #can be case
# #insensitive
# endif()
#find_package(Catch2 REQUIRED)
add_subdirectory(catch2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -fconcepts")
add_executable(Lib List.cpp main.cpp BookEdition.cpp FictionEdition.cpp LearningEdition.cpp ScientificEdition.cpp Table.cpp)
add_executable(Dialog List.cpp dialogMain.cpp BookEdition.cpp FictionEdition.cpp LearningEdition.cpp ScientificEdition.cpp Table.cpp)
add_executable(Tests List.cpp tests.cpp BookEdition.cpp FictionEdition.cpp LearningEdition.cpp ScientificEdition.cpp Table.cpp)
target_link_libraries(Tests PUBLIC Catch2::Catch2)

include(CTest)
include(cmake/Catch.cmake)
catch_discover_tests(Tests)
add_executable(TestList List.cpp Test.cpp BookEdition.cpp  FictionEdition.cpp)