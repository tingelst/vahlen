cmake_minimum_required(VERSION 3.2)
project(vahlen)

# This sets where to look for modules (e.g. "Find*.cmake" files)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11 -O3")

find_package(Eigen3 REQUIRED)

include_directories(include
  ${EIGEN3_INCLUDE_DIR}
)

add_executable(motor src/motor.cpp)
