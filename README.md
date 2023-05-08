# sengine
A custom--unfinished--game engine written in C++

## Setup

### main.cpp
To get started with a basic window and a loop runner active:
```cpp
#include <sengine/include/loop_runners/entity_loop_runner.hpp>
#include <sengine/include/core/engine.hpp>

int main(int argv, char **args) {
    g_Engine->Initialize();

    auto entityLoopRunner = std::make_shared<loopRunners::EntityLoopRunner>();
    g_Engine->AddLoopRunner<loopRunners::EntityLoopRunner>(entityLoopRunner);

    g_Engine->RunLoop();
    return 0;
}
```

### CMake
Put this black magic in your project's CMakeLists.txt:
  
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})  
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

---

### Datafiles
Datafiles are copied to the output directory upon build.

Create a folder in your project's root directory called `datafiles`. Inside that, make another folder called `resources`.

Assets should be stored in `datafiles > resources > assets`. All assets should be placed in their respective sub-folders. The folder is called the non-plural name of the asset type (`texture`, `shader`, `model`, etc.).
