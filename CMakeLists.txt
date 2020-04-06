cmake_minimum_required(VERSION 3.11)

project(RegExp)

aux_source_directory(. DIR_TOOT_SRCS)
add_subdirectory(src)
include_directories(src)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

add_executable(RegExp ${DIR_TOOT_SRCS})
target_link_libraries(RegExp Src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})