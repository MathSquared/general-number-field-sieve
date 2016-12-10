cmake_minimum_required(VERSION 2.8)
project(gnfs)

file(GLOB_RECURSE SOURCES src/*)

find_package(Boost 1.53 REQUIRED)

add_executable(gnfs ${SOURCES})
target_link_libraries(gnfs ${Boost_LIBRARIES})
