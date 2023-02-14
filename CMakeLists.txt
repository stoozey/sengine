cmake_minimum_required(VERSION 3.22)
project(sengine)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE H_FILES include/*.h)
add_library(${PROJECT_NAME} ${SRC_FILES} ${H_FILES})
add_library(sengine::sengine ALIAS sengine)

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_include_directories(${PROJECT_NAME} PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include"
        "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2IMAGE_INCLUDE_DIRS})

target_link_libraries(
        ${PROJECT_NAME} PRIVATE
        --static -static-libgcc -static-libstdc++ -lmingw32 SDL2::SDL2main SDL2::SDL2 SDL2_image::SDL2_image -mconsole)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/internal-datafiles"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/datafiles"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME})