#ifndef SENGINE_INPUT_MANAGER_H
#define SENGINE_INPUT_MANAGER_H

#include <SDL.h>
#include <map>
#include <vector>
#include <utility>
#include <string>

#include "managers/manager.hpp"
#include "structs/vector2.hpp"
#include "enums/input/mouse_button.hpp"
#include "enums/input/input_state.hpp"

namespace managers {
    class InputManager : public Manager {
    public:
        InputManager();
        ~InputManager();

        void Poll();

        void DefineInput(const std::string &inputName);
        void TrackInput(const std::string &inputName, int scanCode);

        structs::Vector2 GetMousePosition();

        int GetMouseDown(enums::MouseButton mouseInput);
        int GetMousePressed(enums::MouseButton mouseInput);
        int GetMouseReleased(enums::MouseButton mouseInput);

        int GetInputDown(const std::string &inputName);
        int GetInputPressed(const std::string &inputName);
        int GetInputReleased(const std::string &inputName);
    private:
        static void SetMapState(std::map<enums::InputState, int> &map, int down);
        static int GetMapState(std::map<enums::InputState, int> &map, enums::InputState inputState);

        int GetInputState(const std::string &inputName, enums::InputState inputState);

        void PollMouse();
        void PollInputs();

        std::map<std::string, std::map<enums::InputState, int>> inputStates;
        std::map<enums::MouseButton, std::map<enums::InputState, int>> mouseStates;

        std::map<std::string, std::vector<int>> keyMap;

        structs::Vector2 mousePosition;
    };
}

#endif //SENGINE_INPUT_MANAGER_H
