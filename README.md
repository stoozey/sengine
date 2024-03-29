# sengine
A custom--unfinished--game engine written in C++

## Setup

### Installing
This is designed to easily be added to your thirdparty folder as a git submodule.
```
cd .\thirdparty\
git submodule add https://github.com/stoozey/sengine.git
git submodule update --init --recursive
```

---

### CMake
Put this black magic in your project's CMakeLists.txt:

```cmake
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(SENGINE_DEBUG)
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})  
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
```

---

### main.cpp
The engine is accessible through a global `g_Engine` pointer.
Before you use the engine, you must call `g_Engine->Initialize()`.
Afterwards, you can add any managers/loop runners you need and then call `g_Engine->RunLoop()`.
Once the loop exits, you should reset the engine pointer to free its resources.

```cpp
#include <core/engine.hpp>
#include <managers/asset_manager.hpp>
#include <loop_runners/entity_loop_runner.hpp>

int main(int argv, char **args) {
    g_Engine->Initialize();
    
    g_Engine->AddManager<managers::AssetManager>();
    g_Engine->AddLoopRunner<loopRunners::EntityLoopRunner>();
    
    g_Engine->RunLoop();
    
    g_Engine.reset();
    return 0;
}
```

---

### Datafiles
Datafiles are copied to the output directory upon build.

Create a folder in your project's root directory called `datafiles`. Inside that, make another folder called `resources`.

Assets should be stored in `datafiles > resources > assets`. All assets should be placed in their respective sub-folders. The folder is called the non-plural name of the asset type (`texture`, `shader`, `model`, etc.).

## Examples
I have a couple of test projects using sengine:
- [Jump King](https://github.com/stoozey/sengine-jump-king)
- [SEngine Asset Creator](https://github.com/stoozey/SEngine-Asset-Creator)
