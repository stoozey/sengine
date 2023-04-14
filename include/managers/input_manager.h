#ifndef SENGINE_INPUT_MANAGER_H
#define SENGINE_INPUT_MANAGER_H

#include <SDL.h>
#include <map>
#include <vector>
#include <utility>
#include <string>

#include "structs/vector2.h"
#include "structs/input/mouse_button.h"
#include "structs/input/input_state.h"

namespace managers {
    class InputManager {
    public:
        InputManager();

        void Poll();

        void DefineInput(const std::string &inputName);
        void TrackInput(const std::string &inputName, int scanCode);

        structs::Vector2 GetMousePosition();

        int GetMouseDown(structs::MouseButton mouseInput);
        int GetMousePressed(structs::MouseButton mouseInput);
        int GetMouseReleased(structs::MouseButton mouseInput);

        int GetInputDown(const std::string &inputName);
        int GetInputPressed(const std::string &inputName);
        int GetInputReleased(const std::string &inputName);
    private:
        std::map<std::string, std::map<structs::InputState, int>> inputStates;
        std::map<structs::MouseButton, std::map<structs::InputState, int>> mouseStates;

        std::map<std::string, std::vector<int>> keyMap;

        structs::Vector2 mousePosition;

        void PollMouse();
        void PollInputs();

        void SetMapState(std::map<structs::InputState, int> &map, int down);
        int GetMapState(std::map<structs::InputState, int> &map, structs::InputState inputState);
    };
}

extern managers::InputManager *g_InputManager;

#endif //SENGINE_INPUT_MANAGER_H
