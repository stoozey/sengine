#include <spdlog/spdlog.h>

#include "managers/input_manager.hpp"
#include "core/engine.hpp"
#include "structs/input/mouse_button.hpp"
#include "structs/input/input_state.hpp"

managers::InputManager *g_InputManager = new managers::InputManager();

namespace managers {
    InputManager::InputManager() : mousePosition() {
        for (int i = (int) structs::MouseButton::LeftClick; i != (int) structs::MouseButton::None; i++) {
            std::map<structs::InputState, int> map = {
                    { structs::InputState::Down,     0 },
                    { structs::InputState::Pressed,  0 },
                    { structs::InputState::Released, 0 }
            };

            auto mouseInput = static_cast<structs::MouseButton>(i);
            mouseStates.insert(std::pair<structs::MouseButton, std::map<structs::InputState, int>>(mouseInput, map));
        }
    }

    void InputManager::Poll() {
        PollMouse();
        PollInputs();
    }

    void InputManager::PollMouse() {
        // mouse pos
        int mouseX, mouseY;
        const Uint32 mouseInputs = SDL_GetMouseState(&mouseX, &mouseY);
        SDL_RenderWindowToLogical(g_Engine->GetRenderer(), mouseX, mouseY, &mousePosition.x, &mousePosition.y);

        // set map
        SetMapState(mouseStates.find(structs::MouseButton::LeftClick)->second, (mouseInputs & SDL_BUTTON_LMASK));
        SetMapState(mouseStates.find(structs::MouseButton::MiddleClick)->second, (mouseInputs & SDL_BUTTON_MMASK));
        SetMapState(mouseStates.find(structs::MouseButton::RightClick)->second, (mouseInputs & SDL_BUTTON_RMASK));
    }

    void InputManager::PollInputs() {
        const Uint8 *keyInputs = const_cast <Uint8 *> (SDL_GetKeyboardState(nullptr));
        for (auto &pair: keyMap) {
            std::string name = pair.first;
            std::vector<int> scanCodes = pair.second;

            int isDown = 0;
            for (int scanCode: scanCodes) {
                if (keyInputs[scanCode] != 0) {
                    isDown = 1;
                    break;
                }
            }

            SetMapState(inputStates.find(name)->second, isDown);
        }
    }

    void InputManager::SetMapState(std::map<structs::InputState, int> &map, int isDown) {
        auto down = map.find(structs::InputState::Down);
        auto pressed = map.find(structs::InputState::Pressed);
        auto released = map.find(structs::InputState::Released);

        int downPrevious = down->second;
        map[structs::InputState::Released] = ((downPrevious) && (!isDown));
        map[structs::InputState::Pressed] = ((!downPrevious) && (isDown));
        map[structs::InputState::Down] = isDown;
    }

    int InputManager::GetMapState(std::map<structs::InputState, int> &map, structs::InputState inputState) {
        return map.find(inputState)->second;
    }

    int InputManager::GetInputState(const std::string &inputName, structs::InputState inputState) {
        auto find = inputStates.find(inputName);
        if (find == inputStates.end()) {
            spdlog::warn("tried to detect non-defined input \"{}\"", inputName);
            return 0;
        }

        std::map<structs::InputState, int> map = find->second;
        return GetMapState(map, inputState);
    }

    int InputManager::GetMouseDown(structs::MouseButton mouseInput) {
        auto state = mouseStates.find(mouseInput)->second;
        return GetMapState(state, structs::InputState::Down);
    }

    int InputManager::GetMousePressed(structs::MouseButton mouseInput) {
        auto state = mouseStates.find(mouseInput)->second;
        return GetMapState(state, structs::InputState::Pressed);
    }

    int InputManager::GetMouseReleased(structs::MouseButton mouseInput) {
        auto state = mouseStates.find(mouseInput)->second;
        return GetMapState(state, structs::InputState::Released);
    }

    structs::Vector2 InputManager::GetMousePosition() {
        return mousePosition;
    }

    void InputManager::DefineInput(const std::string &inputName) {
        std::vector<int> keysVector;
        keyMap.insert(std::pair<std::string, std::vector<int>>(inputName, keysVector));

        std::map<structs::InputState, int> map;
        map[structs::InputState::Down] = 0;
        map[structs::InputState::Pressed] = 0;
        map[structs::InputState::Released] = 0;

        inputStates.insert(std::pair<std::string, std::map<structs::InputState, int>>(inputName, map));
    }

    void InputManager::TrackInput(const std::string &inputName, int scanCode) {
        auto find = keyMap.find(inputName);
        if (find == keyMap.end()) return spdlog::warn("tried to track non-defined input \"{}\"", inputName);

        std::vector<int> &scanCodes = find->second;
        scanCodes.emplace_back(scanCode);
    }

    int InputManager::GetInputDown(const std::string &inputName) {
        return GetInputState(inputName, structs::InputState::Down);
    }

    int InputManager::GetInputPressed(const std::string &inputName) {
        return GetInputState(inputName, structs::InputState::Pressed);
    }

    int InputManager::GetInputReleased(const std::string &inputName) {
        return GetInputState(inputName, structs::InputState::Released);
    }
}