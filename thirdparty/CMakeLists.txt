cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)

# header-only
target_include_directories(${PROJECT_NAME} PUBLIC KHR base64 boost dlg freetype)

# zlib
set(CMAKE_POLICY_DEFAULT_CMP0048 NEW)
set(SKIP_INSTALL_ALL ON)

add_subdirectory(zlib EXCLUDE_FROM_ALL)
set(ZLIB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/zlib" "${CMAKE_CURRENT_BINARY_DIR}/zlib")
set(ZLIB_LIBRARY zlibstatic)
set(ZLIB_FOUND TRUE)
set(ZLIB_LIBRARIES zlibstatic)
set(ASSIMP_BUILD_ZLIB OFF)

add_library(3rdparty_zlib INTERFACE)
target_link_libraries(3rdparty_zlib INTERFACE ${ZLIB_LIBRARY})
target_include_directories(3rdparty_zlib INTERFACE ${ZLIB_INCLUDE_DIR})

# assimp
#set(ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF)
#set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF)
#set(ASSIMP_BUILD_OBJ_IMPORTER ON)

add_subdirectory(assimp)

# other
add_subdirectory(glm)
add_subdirectory(stb)
add_subdirectory(glad)
add_subdirectory(spdlog)
add_subdirectory(entt)
add_subdirectory(crossguid)
add_subdirectory(nativefiledialog-extended)
add_subdirectory(imgui)