#include <Arduino.h>
#include <Clock.h>
#include <Matrix.h>
#include <InputManager.h>
#include <StateManager.h>
#include <ServerManager.h>

EspSettings settings = {"IDnet-10", "ArtS1975", 80, "myToken"};
//EspSettings settings = {"}:-)", "vv1976JR", 80, "myToken"};

InputManager _inputManager;
Clock _clock;
Matrix _matrix;
StateManager _stateManager;
ServerManager _serverManager(settings);

void setup() {
  Serial.begin(9600);
  
  Serial.println("LED Matrix Project Initialized");

  _inputManager.init();
  _clock.init();
  _matrix.init();
  _matrix.off();
  _serverManager.init();
}

void loop() {
  _inputManager.update(_stateManager);
  _matrix.update(_stateManager, _clock);
  _serverManager.update();
}
