#include <Arduino.h>
#include <Clock.h>
#include <Touch.h>
#include <Matrix.h>
#include <StateManager.h>

Clock _clock;
Touch _touch;
Matrix _matrix;
StateManager _stateManager;
State lastState = State::OFF;

void printClock()
{
  Serial.println("Clock Initialized");
  Serial.print("Current Time: ");

  std::array<byte, 3> currentTime = _clock.getTime();
  Serial.print(currentTime[0], DEC);
  Serial.print(":");
  Serial.print(currentTime[1], DEC);
  Serial.print(":");
  Serial.println(currentTime[2], DEC);

  Serial.print("Current Date: ");
  std::array<byte, 3> currentDate = _clock.getDate();
  Serial.print(currentDate[0], DEC);
  Serial.print("/");
  Serial.print(currentDate[1], DEC);
  Serial.print("/");
  Serial.println(currentDate[2], DEC);

  Serial.print(" Day of Week: ");
  byte currentDOW = _clock.getDOW();
  Serial.println(currentDOW, DEC);
}

void stateChange(){
  if(_touch.isDouble()){
      _stateManager.nextState();
      Serial.println("State changed to: " + String(static_cast<int>(_stateManager.getState())));
    }
}

void handleEffects() {
  _matrix.update();
  stateChange();
  if(_touch.isTouched()) {
    _matrix.nextEffect();
    Serial.print("Next effect selected: ");
    Serial.println(_matrix.getEffectName());
  }
}

void handleClock() {
  printClock();
  stateChange();
}

void handleOff() {
  _matrix.clear();
}

void setup() {
  Serial.begin(115200);
  delay(500); 
  Serial.flush();
  
  Serial.println("LED Matrix Project Initialized");

  _touch.init();
  _clock.init();
  _matrix.init();
  printClock();
}

void loop() {
  _touch.update();

  if (_touch.isHolded()) {
    _stateManager.powerSwitch();
    Serial.println("Power switch toggled. Current state: " + String(static_cast<int>(_stateManager.getState())));
  }

  State currentState = _stateManager.getState();

  // Обработка при смене состояния
  if (currentState != lastState) {
    if (currentState == State::OFF) {
      _matrix.clear();
    }
    lastState = currentState;
  }

  switch (currentState) {
    case State::EFFECTS: handleEffects();
      break;
    case State::CLOCK: handleClock();
      break;
    case State::OFF:
      break;
  }
}