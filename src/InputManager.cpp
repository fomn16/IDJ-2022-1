#include "InputManager.hpp"

InputManager InputManager::instance;

InputManager::InputManager(){
    //variáveis estão sendo iniciadas (atribuídas um valor default) no .hpp
}

InputManager::~InputManager(){

}


InputManager& InputManager::GetInstance(){
    return InputManager::instance;
}

void InputManager::Update(){
    SDL_Event event;
    updateCounter++;

    SDL_GetMouseState(&mouseX, &mouseY);
    quitRequested = false;

    while (SDL_PollEvent(&event)) {
        if(!event.key.repeat){
            // Se o evento for quit, setar a flag para terminação
            if(event.type == SDL_QUIT) {
                quitRequested = true;
            }

            // Se o evento for clique ou soltar mouse
            if(event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
                mouseState[event.button.button] = event.type == SDL_MOUSEBUTTONDOWN;
                mouseUpdate[event.button.button] = updateCounter;
            }

            //Se o evento for pressionamento ou soltar tecla
            if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
                keyState[event.key.keysym.sym] = event.type == SDL_KEYDOWN;
                keyUpdate[event.key.keysym.sym] = updateCounter;
            }
        }
    }
}

bool InputManager::KeyPress(int key){
    //verificando se chave já foi adicionada aos mapas
    if(keyState.find(key) == keyState.end())
        return false;
    return keyState[key] && (keyUpdate[key] == updateCounter);
}

bool InputManager::KeyRelease(int key){
    //verificando se chave já foi adicionada aos mapas
    if(keyState.find(key) == keyState.end())
        return false;
    return !keyState[key] && (keyUpdate[key] == updateCounter);
}

bool InputManager::IsKeyDown(int key){
    //verificando se chave já foi adicionada aos mapas
    if(keyState.find(key) == keyState.end())
        return false;
    return keyState[key];
}

bool InputManager::MousePress(int button){
    //verificando se chave já foi adicionada aos mapas
    if(mouseState.find(button) == mouseState.end())
        return false;
    return mouseState[button] && (mouseUpdate[button] == updateCounter);
}

bool InputManager::MouseRelease(int button){
    //verificando se chave já foi adicionada aos mapas
    if(mouseState.find(button) == mouseState.end())
        return false;
    return !mouseState[button] && (mouseUpdate[button] == updateCounter);
}

bool InputManager::IsMouseDown(int button){
    //verificando se chave já foi adicionada aos mapas
    if(mouseState.find(button) == mouseState.end())
        return false;
    return mouseState[button];
}

int InputManager::GetMouseX(){
    return mouseX;
}

int InputManager::GetMouseY(){
    return mouseY;
}

bool InputManager::QuitRequested(){
    return quitRequested;
}