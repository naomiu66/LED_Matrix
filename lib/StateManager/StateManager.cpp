#include <StateManager.h>

State StateManager::getState() {
    return state;
}

void StateManager::nextState() {
    switch (state) {
        case State::EFFECTS: state = State::CLOCK; break;
        case State::CLOCK: state = State::EFFECTS; break;
        case State::OFF: break;
    }
}

void StateManager::powerSwitch()
{
    if(state == State::OFF){
        state = State::EFFECTS;
    } else {
        state = State::OFF;
    }
}
