cmake_minimum_required(VERSION 3.17)
project(AdventOfCode2021)

set(CMAKE_CXX_STANDARD 20)

set(UTILS utils.cpp utils.h Position.cpp Position.h)

add_executable(template day_0.cpp ${UTILS})
configure_file(data/input_day_0.txt ${CMAKE_BINARY_DIR}/ COPYONLY)

add_executable(day_01 day_01.cpp ${UTILS})
configure_file(data/input_day_1.txt ${CMAKE_BINARY_DIR}/ COPYONLY)

add_executable(day_02 day_02.cpp ${UTILS})
configure_file(data/input_day_2.txt ${CMAKE_BINARY_DIR}/ COPYONLY)

add_executable(day_03 day_03.cpp ${UTILS})
configure_file(data/input_day_3.txt ${CMAKE_BINARY_DIR}/ COPYONLY)

add_executable(day_05 day_05.cpp ${UTILS})
configure_file(data/input_day_5.txt ${CMAKE_BINARY_DIR}/ COPYONLY)

add_executable(day_06 day_06.cpp ${UTILS})
configure_file(data/input_day_6.txt ${CMAKE_BINARY_DIR}/ COPYONLY)

add_executable(day_07 day_07.cpp ${UTILS})
configure_file(data/input_day_7.txt ${CMAKE_BINARY_DIR}/ COPYONLY)
target_compile_features(day_07 PRIVATE cxx_std_17)

add_executable(day_08 day_08.cpp ${UTILS})
configure_file(data/input_day_8.txt ${CMAKE_BINARY_DIR}/ COPYONLY)

add_executable(day_09 day_09.cpp ${UTILS})
configure_file(data/input_day_9.txt ${CMAKE_BINARY_DIR}/ COPYONLY)

add_executable(day_10 day_10.cpp ${UTILS})
configure_file(data/input_day_10.txt ${CMAKE_BINARY_DIR}/ COPYONLY)

add_executable(day_11 day_11.cpp ${UTILS})
configure_file(data/input_day_11.txt ${CMAKE_BINARY_DIR}/ COPYONLY)
