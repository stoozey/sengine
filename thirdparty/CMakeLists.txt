cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(glm)
add_subdirectory(stb)
add_subdirectory(assimp)
add_subdirectory(glad)
add_subdirectory(spdlog)

target_include_directories(${PROJECT_NAME} PUBLIC KHR base64 boost)