cmake_minimum_required(VERSION 3.17)
project(AdventOfCode2021)

set(CMAKE_CXX_STANDARD 20)

set(UTILS utils.cpp utils.h)

add_executable(template day_0.cpp ${UTILS})
configure_file(data/input_day_0.txt ${CMAKE_BINARY_DIR}/ COPYONLY)

add_executable(day_01 day_01.cpp ${UTILS})
configure_file(data/input_day_1.txt ${CMAKE_BINARY_DIR}/ COPYONLY)

add_executable(day_02 day_02.cpp ${UTILS})
configure_file(data/input_day_2.txt ${CMAKE_BINARY_DIR}/ COPYONLY)
