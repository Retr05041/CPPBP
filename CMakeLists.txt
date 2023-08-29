cmake_minimum_required(VERSION 3.0)
project(CPPBP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_definitions(-std=c++20)

# Includes
set(CMAKE_MODULE_PATH ${G52CPP_SOURCE_DIR}/cmake)


set(SOURCE_FILES src/Main.cpp
    src/problem/Problem.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})