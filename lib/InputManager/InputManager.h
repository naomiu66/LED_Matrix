#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <Touch.h>
#include <StateManager.h>

class InputManager {

public: 
    void init();
    void update(StateManager &stateManager);

private:
    Touch _touch;
};

#endif