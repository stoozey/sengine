cmake_minimum_required(VERSION 3.22)

add_subdirectory(glm)
add_subdirectory(stb)

target_include_directories(${PROJECT_NAME} PUBLIC KHR glad)