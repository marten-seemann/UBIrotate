cmake_minimum_required(VERSION 2.8)
project(UBIrotate C CXX)

file(GLOB CPPS src/*.cpp src/*.c)
file(GLOB HEADERS include/*.h)

find_package(Boost REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(include .)

add_executable(UBIrotate ${HEADERS} ${CPPS})
target_link_libraries(UBIrotate ${Boost_LIBRARIES})

SET(CMAKE_VERBOSE_MAKEFILE ON)


install (TARGETS UBIrotate CONFIGURATION Release DESTINATION bin)
