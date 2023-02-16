#include "managers/input_manager.h"
#include "engine.h"

InputManager *g_InputManager = new InputManager();

InputManager::InputManager() {
    for (int i = (int) MouseButton::LeftClick; i != (int) MouseButton::None; i++) {
        std::map<Input, int> map = {
                {Input::Down, 0},
                {Input::Pressed, 0},
                {Input::Released, 0}
        };
        MouseButton mouseInput = static_cast<MouseButton>(i);
        mouseStates.insert(std::pair<MouseButton, std::map<Input, int>>(mouseInput, map));
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
    SetMapState(mouseStates.find(MouseButton::LeftClick)->second, (mouseInputs & SDL_BUTTON_LMASK));
    SetMapState(mouseStates.find(MouseButton::MiddleClick)->second, (mouseInputs & SDL_BUTTON_MMASK));
    SetMapState(mouseStates.find(MouseButton::RightClick)->second, (mouseInputs & SDL_BUTTON_RMASK));
}

void InputManager::PollInputs() {
    const Uint8 *keyInputs = const_cast <Uint8*> (SDL_GetKeyboardState(nullptr));
    for (auto &pair : keyMap) {
        std::string name = pair.first;
        std::vector<int> scanCodes = pair.second;

        int isDown = 0;
        for (int i = 0; i < scanCodes.size(); i++) {
            int scanCode = scanCodes[i];
            if (keyInputs[scanCode] != 0)
            {
                isDown = 1;
                break;
            }
        }

        SetMapState(inputStates.find(name)->second, isDown);
    }
}

int InputManager::GetMapState(std::map<Input, int> &map, Input inputState) {
    return map.find(inputState)->second;
}

void InputManager::SetMapState(std::map<Input, int> &map, int isDown) {
    auto down = map.find(Input::Down);
    auto pressed = map.find(Input::Pressed);
    auto released = map.find(Input::Released);

    int downPrevious = down->second;
    map[Input::Released] = ((downPrevious) && (!isDown));
    map[Input::Pressed] = ((!downPrevious) && (isDown));
    map[Input::Down] = isDown;
}

int InputManager::GetMouseDown(MouseButton mouseInput) {
    auto state = mouseStates.find(mouseInput)->second;
    return GetMapState(state, Input::Down);
}

int InputManager::GetMousePressed(MouseButton mouseInput) {
    auto state = mouseStates.find(mouseInput)->second;
    return GetMapState(state, Input::Pressed);
}

int InputManager::GetMouseReleased(MouseButton mouseInput) {
    auto state = mouseStates.find(mouseInput)->second;
    return GetMapState(state, Input::Released);
}

Vector2 InputManager::GetMousePosition() {
    return mousePosition;
}

void InputManager::DefineInput(std::string inputName) {
    std::vector<int> keysVector;
    keyMap.insert(std::pair<std::string, std::vector<int>>(inputName, keysVector));

    std::map<Input, int> map;
    map[Input::Down] = 0;
    map[Input::Pressed] = 0;
    map[Input::Released] = 0;

    inputStates.insert(std::pair<std::string, std::map<Input, int>>(inputName, map));
}

void InputManager::TrackInput(std::string name, int scanCode) {
    auto keys = keyMap.find(name);
    std::vector<int> &scanCodes = keys->second;
    scanCodes.emplace_back(scanCode);
}

int InputManager::GetInputDown(std::string name) {
    auto state = inputStates.find(name)->second;
    return GetMapState(state, Input::Down);
}

int InputManager::GetInputPressed(std::string name) {
    auto state = inputStates.find(name)->second;
    return GetMapState(state, Input::Pressed);
}

int InputManager::GetInputReleased(std::string name) {
    auto state = inputStates.find(name)->second;
    return GetMapState(state, Input::Released);
}