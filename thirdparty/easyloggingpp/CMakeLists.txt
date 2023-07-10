cmake_minimum_required(VERSION 3.22)

project(easyloggingpp)

add_library(${PROJECT_NAME} STATIC src/easylogging++.cc)

target_include_directories(${PROJECT_NAME} PUBLIC include/)