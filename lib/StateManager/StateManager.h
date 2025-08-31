#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

enum class State{
    EFFECTS,
    CLOCK,
    OFF
};

class StateManager {
public:
    State getState();
    void nextState();
    void powerSwitch();
    bool isEffectChanged() { return _effectChanged; }
    void setEffectChanged(bool effectChanged) { _effectChanged = effectChanged; }

private:
    State state = State::OFF;
    bool _effectChanged = false;
};

#endif