cmake_minimum_required(VERSION 3.22)

project(flecs)

add_library(${PROJECT_NAME} src/flecs.c include/flecs.h)
target_include_directories(${PROJECT_NAME} PUBLIC include/)