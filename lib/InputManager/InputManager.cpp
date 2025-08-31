#include <InputManager.h>

void InputManager::init() {
    _touch.init();
}

void InputManager::update(StateManager &stateManager) {
    _touch.update();

    State currentState = stateManager.getState();

    if(_touch.isHolded()) {
        stateManager.powerSwitch();
        Serial.println("holded");
        Serial.print("current state: ");
        Serial.println(static_cast<int>(stateManager.getState()));
    }
    else if (_touch.isTouched() && currentState == State::EFFECTS) {
        stateManager.setEffectChanged(true);
    }
    else if (_touch.isDouble()){
        stateManager.nextState();
    }
}