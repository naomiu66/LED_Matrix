#include <Arduino.h>
#include <Clock.h>
#include <Touch.h>
#include <Matrix.h>
#include <StateManager.h>
#include <ServerManager.h>

EspSettings settings = {"IDnet-10", "ArtS1975", 80, "myToken"};

Clock _clock;
Touch _touch;
Matrix _matrix;
StateManager _stateManager;
ServerManager _serverManager(settings);

State lastState = State::OFF;
byte lastHour = 0, lastMinute = 0, lastDay = 0, lastMonth = 0, lastYear = 0;

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
      _matrix.clear();
      Serial.println("State changed to: " + String(static_cast<int>(_stateManager.getState())));
    }
}

void handleEffects() {
  _matrix.playEffect();
  stateChange();
  if(_touch.isTouched()) {
    _matrix.nextEffect();
    Serial.print("Next effect selected: ");
    Serial.println(_matrix.getEffectName());
  }
}

void handleClock() {
  std::array<byte, 3> time = _clock.getTime();
  std::array<byte, 3> date = _clock.getDate();
  if(time[0] != lastHour || time[1] != lastMinute || date[2] != lastDay || date[1] != lastMonth || date[0] != lastYear) {
    _matrix.clear();
    delay(1);
    lastHour = time[0];
    lastMinute = time[1];
    lastDay = date[2];
    lastMonth = date[1];
    lastYear = date[0];
    _matrix.playClock(time[0], time[1], date[2], date[1], date[0]);
    printClock();
  } 
  stateChange();
}

void handleOff() {
  _matrix.clear();
}

void setup() {
  Serial.begin(9600);
  
  Serial.println("LED Matrix Project Initialized");

  _serverManager.init();

  _touch.init();
  _clock.init();
  _matrix.init();
  _matrix.clear();
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
    else if (currentState == State::CLOCK){
      _matrix.clear();
      delay(1);
      _matrix.playClock(lastHour, lastMinute, lastDay, lastMonth, lastYear);
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

  _serverManager.update();
}