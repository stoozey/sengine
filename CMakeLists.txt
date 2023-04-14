cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)
project(sengine VERSION 1.0.0 DESCRIPTION "taking a mean shit right now!")

include(GNUInstallDirs)

# source files
file(GLOB_RECURSE SENGINE_SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/src/*.c")
file(GLOB_RECURSE SENGINE_INCLUDE_FILES "${PROJECT_SOURCE_DIR}/include/*.h")
add_library(${PROJECT_NAME} SHARED ${SENGINE_SRC_FILES} ${SENGINE_INCLUDE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>"
        )

set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION "${PROJECT_VERSION}"
        SOVERSION "${PROJECT_VERSION_MAJOR}"
        PUBLIC_HEADER "${SENGINE_INCLUDE_FILES}"
        )

# packages
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2IMAGE_INCLUDE_DIRS})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${SDL2IMAGE_INCLUDE_DIRS})

set(SENGINE_SDL_LINKER_FLAGS SDL2::SDL2main SDL2::SDL2 SDL2_image::SDL2_image)

target_link_libraries(${PROJECT_NAME} PRIVATE ${SENGINE_SDL_LINKER_FLAGS})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE --static -static-libstdc++ -static-libgcc -lmingw32 ${SENGINE_SDL_LINKER_FLAGS} -mconsole)

# thirdparty
add_subdirectory(thirdparty)
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty)
target_link_libraries(${PROJECT_NAME} PUBLIC assimp)
target_link_libraries(${PROJECT_NAME} PUBLIC glm)
target_link_libraries(${PROJECT_NAME} PUBLIC stb)
target_link_libraries(${PROJECT_NAME} PUBLIC glad)

# build commands
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/internal-datafiles"
        $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/datafiles"
        $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>)


install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )