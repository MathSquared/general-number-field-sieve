cmake_minimum_required(VERSION 2.8)
project(gnfs)

set(CMAKE_CXX_FLAGS "-std=c++0x")

file(GLOB_RECURSE SOURCES src/*)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

find_package(GMP REQUIRED)
find_package(NTL REQUIRED)

add_executable(gnfs ${SOURCES})
target_link_libraries(gnfs ${GMP_LIBRARIES} ${NTL_LIBRARY})
