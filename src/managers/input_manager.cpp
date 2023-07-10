#include "managers/input_manager.hpp"
#include "core/engine.hpp"
#include "core/log.hpp"
#include "enums/input/mouse_button.hpp"
#include "enums/input/input_state.hpp"

namespace managers {
    InputManager::InputManager() : mousePosition() {
        for (int i = (int) enums::MouseButton::LeftClick; i != (int) enums::MouseButton::None; i++) {
            std::map<enums::InputState, int> map = {
                    { enums::InputState::Down,     0 },
                    { enums::InputState::Pressed,  0 },
                    { enums::InputState::Released, 0 }
            };

            auto mouseInput = static_cast<enums::MouseButton>(i);
            mouseStates.insert(std::pair<enums::MouseButton, std::map<enums::InputState, int>>(mouseInput, map));
        }
    }

    InputManager::~InputManager() = default;

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
        SetMapState(mouseStates.find(enums::MouseButton::LeftClick)->second, (mouseInputs & SDL_BUTTON_LMASK));
        SetMapState(mouseStates.find(enums::MouseButton::MiddleClick)->second, (mouseInputs & SDL_BUTTON_MMASK));
        SetMapState(mouseStates.find(enums::MouseButton::RightClick)->second, (mouseInputs & SDL_BUTTON_RMASK));
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

    void InputManager::SetMapState(std::map<enums::InputState, int> &map, int isDown) {
        auto down = map.find(enums::InputState::Down);
        auto pressed = map.find(enums::InputState::Pressed);
        auto released = map.find(enums::InputState::Released);

        int downPrevious = down->second;
        map[enums::InputState::Released] = ((downPrevious) && (!isDown));
        map[enums::InputState::Pressed] = ((!downPrevious) && (isDown));
        map[enums::InputState::Down] = isDown;
    }

    int InputManager::GetMapState(std::map<enums::InputState, int> &map, enums::InputState inputState) {
        return map.find(inputState)->second;
    }

    int InputManager::GetInputState(const std::string &inputName, enums::InputState inputState) {
        auto find = inputStates.find(inputName);
        if (find == inputStates.end()) {
            core::Log::Warn(fmt::format("tried to detect non-defined input \"{}\"", inputName));
            return 0;
        }

        std::map<enums::InputState, int> map = find->second;
        return GetMapState(map, inputState);
    }

    int InputManager::GetMouseDown(enums::MouseButton mouseInput) {
        auto state = mouseStates.find(mouseInput)->second;
        return GetMapState(state, enums::InputState::Down);
    }

    int InputManager::GetMousePressed(enums::MouseButton mouseInput) {
        auto state = mouseStates.find(mouseInput)->second;
        return GetMapState(state, enums::InputState::Pressed);
    }

    int InputManager::GetMouseReleased(enums::MouseButton mouseInput) {
        auto state = mouseStates.find(mouseInput)->second;
        return GetMapState(state, enums::InputState::Released);
    }

    structs::Vector2 InputManager::GetMousePosition() {
        return mousePosition;
    }

    void InputManager::DefineInput(const std::string &inputName) {
        std::vector<int> keysVector;
        keyMap.insert(std::pair<std::string, std::vector<int>>(inputName, keysVector));

        std::map<enums::InputState, int> map;
        map[enums::InputState::Down] = 0;
        map[enums::InputState::Pressed] = 0;
        map[enums::InputState::Released] = 0;

        inputStates.insert(std::pair<std::string, std::map<enums::InputState, int>>(inputName, map));
    }

    void InputManager::TrackInput(const std::string &inputName, int scanCode) {
        auto find = keyMap.find(inputName);
        if (find == keyMap.end()) return core::Log::Warn(fmt::format("tried to track non-defined input \"{}\"", inputName));

        std::vector<int> &scanCodes = find->second;
        scanCodes.emplace_back(scanCode);
    }

    int InputManager::GetInputDown(const std::string &inputName) {
        return GetInputState(inputName, enums::InputState::Down);
    }

    int InputManager::GetInputPressed(const std::string &inputName) {
        return GetInputState(inputName, enums::InputState::Pressed);
    }

    int InputManager::GetInputReleased(const std::string &inputName) {
        return GetInputState(inputName, enums::InputState::Released);
    }
}