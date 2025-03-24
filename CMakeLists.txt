cmake_minimum_required(VERSION 3.20.0)
project(targemtest2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${CMAKE_PROJECT_NAME}
    "src/main.cpp" "src/String.h" "src/String.cpp")
