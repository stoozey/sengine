cmake_minimum_required(VERSION 3.22)

project(glad)

add_library(${PROJECT_NAME} src/glad.c include/glad.h)
target_include_directories(${PROJECT_NAME} PUBLIC include/)