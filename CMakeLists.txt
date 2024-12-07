cmake_minimum_required(VERSION 3.5.0)
project(csv VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
add_executable(csv main.cpp csv/csv.cpp)