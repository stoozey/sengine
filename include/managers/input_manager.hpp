#ifndef SENGINE_INPUT_MANAGER_H
#define SENGINE_INPUT_MANAGER_H

#include <SDL.h>
#include <map>
#include <vector>
#include <utility>
#include <string>

#include "managers/manager.hpp"
#include "structs/vector2.hpp"
#include "structs/input/mouse_button.hpp"
#include "structs/input/input_state.hpp"

namespace managers {
    class InputManager : public Manager {
    public:
        InputManager();
        ~InputManager();

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
        static void SetMapState(std::map<structs::InputState, int> &map, int down);
        static int GetMapState(std::map<structs::InputState, int> &map, structs::InputState inputState);

        int GetInputState(const std::string &inputName, structs::InputState inputState);

        void PollMouse();
        void PollInputs();

        std::map<std::string, std::map<structs::InputState, int>> inputStates;
        std::map<structs::MouseButton, std::map<structs::InputState, int>> mouseStates;

        std::map<std::string, std::vector<int>> keyMap;

        structs::Vector2 mousePosition;
    };
}

#endif //SENGINE_INPUT_MANAGER_H
