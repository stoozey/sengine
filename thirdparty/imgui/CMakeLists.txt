cmake_minimum_required(VERSION 3.22)

project(imgui)

add_library(
        ${PROJECT_NAME}

        src/imgui.cpp
        src/imgui_draw.cpp
        src/imgui_tables.cpp
        src/imgui_widgets.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC include/)