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

private:
    State state = State::OFF;
};

#endif