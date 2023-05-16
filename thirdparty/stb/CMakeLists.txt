cmake_minimum_required(VERSION 3.22)

project(stb)

add_library(${PROJECT_NAME} STATIC src/stb.cpp include/stb.h)
target_include_directories(${PROJECT_NAME} PUBLIC include)