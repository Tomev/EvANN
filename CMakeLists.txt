cmake_minimum_required(VERSION 3.5)
project(GenEvANN)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp GA/individual.h GA/individual.cpp GA/individual.h NN/neuron.cpp NN/neuron.h GA/population.cpp GA/population.h)
add_executable(GenEvANN ${SOURCE_FILES} GA/individual.h GA/individual.cpp GA/individual.h)