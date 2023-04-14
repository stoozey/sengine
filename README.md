# SEngine-2
A custom game engine written in C++

## Setup

### CMake
Put this black magic in your project's CMakeLists.txt:
  
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})  
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

---

### Datafiles
Create a folder in your project's root directory called `datafiles`. Inside that, make another folder called `assets`. All assets should be placed in their respective sub-folders inside the `assets` folder. (See `structs/asset_path.h` for the folder names)
