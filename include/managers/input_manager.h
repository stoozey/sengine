#ifndef SENGINE_INPUT_MANAGER_H
#define SENGINE_INPUT_MANAGER_H

#include <SDL.h>
#include <map>
#include <vector>
#include <utility>
#include <string>

#include "datatypes/vector2.h"

enum class MouseButton {
    LeftClick,
    MiddleClick,
    RightClick,
    None,
};

enum class Input {
    Pressed,
    Down,
    Released,
};

class InputManager {
public:
    InputManager();

    void Poll();

    void DefineInput(const std::string &inputName);
    void TrackInput(const std::string &inputName, int scanCode);

    int GetMouseDown(MouseButton mouseInput);
    int GetMousePressed(MouseButton mouseInput);
    int GetMouseReleased(MouseButton mouseInput);
    Vector2 GetMousePosition();

    int GetInputDown(const std::string &inputName);
    int GetInputPressed(const std::string &inputName);
    int GetInputReleased(const std::string &inputName);
private:
    void PollMouse();
    void PollInputs();

    void SetMapState(std::map<Input, int> &map, int down);
    int GetMapState(std::map<Input, int> &map, Input inputState);

    std::map<std::string, std::map<Input, int>> inputStates;
    std::map<MouseButton, std::map<Input, int>> mouseStates;

    std::map<std::string, std::vector<int>> keyMap;

    Vector2 mousePosition;
};

extern InputManager *g_InputManager;

#endif //SENGINE_INPUT_MANAGER_H
