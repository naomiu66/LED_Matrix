#include <Matrix.h>

void Matrix::init() {
    FastLED.addLeds<WS2811, MATRIX_PIN, GRB>(leds, MATRIX_SIZE);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, POWER_LIMIT);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.clearData();
    FastLED.show();

    effects[0] = &confetti;
    effects[1] = &fire;
    effects[2] = &snow;
    effectsCount = 3;
    currentEffect = 0;

    for (int i = 0; i < effectsCount; i++) {
        effects[i]->init();
    }
    Serial.println("Matrix initialized with WS2811 chipset on pin " + String(MATRIX_PIN));
}

void Matrix::update(StateManager &stateManager, Clock& clock)
{
    State currentState = stateManager.getState();
    bool stateChanged = currentState != lastState;
    bool effectChanged = stateManager.isEffectChanged();
    if(stateChanged) lastState = currentState;
    std::array<byte, 3> time = clock.getTime();

    switch(currentState){
        case State::EFFECTS: 
            if(effectChanged){
                nextEffect();
                stateManager.setEffectChanged(false);
            }
            playEffect(); 
            break;
        case State::CLOCK: 
            if(clock.isTimeChanged() || stateChanged) {

                playClock(time[0], time[1]);
            }
            break;
        case State::OFF: 
            if(stateChanged){
                off();
            }
            break;
    }
}

void Matrix::drawPixel(int x, int y, CRGB color) {
    if(x < 0 || x >= MATRIX_WIDTH || y < 0 || y >= MATRIX_HEIGHT){
        Serial.println("Error: Pixel coordinates out of bounds.");
        return;
    }

    int flippedY = MATRIX_HEIGHT - 1 - y;

    int index;
    if (flippedY % 2 == 0) {
        index = flippedY * MATRIX_WIDTH + x;
    } else {
        index = flippedY * MATRIX_WIDTH + (MATRIX_WIDTH - 1 - x);
    }
    leds[index] = color;
}

void Matrix::clear(){
    FastLED.clearData();
}

void Matrix::off()
{
    FastLED.clearData();
    FastLED.show();
}

void Matrix::setBrightness(int brightness){
    if(brightness < 0 || brightness > 255){
        Serial.println("Error: Brightness value out of range (0-255).");
        return;
    }
    FastLED.setBrightness(brightness);
}

void Matrix::fillScreen(CRGB color)
{
    for(int i = 0; i < MATRIX_SIZE; i++) 
    {
        leds[i] = color;
    }
    FastLED.show();
}

void Matrix::drawDigit(int digit, int x, int y)
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            if ((DIGITS_3X5[digit][i] >> (2-j)) & 1) {
                drawPixel(x + j, y + i, CRGB::White);
            }
        }
    }
}

void Matrix::drawColon(int x, int y)
{
    for (int i = 0; i < 5; i++) {
        if (COLON[i] & 0b010) {
            drawPixel(x, y + i, CRGB::White);
        }
    }
}

void Matrix::playEffect(){
    effects[currentEffect]->update(leds);
    FastLED.show();
}

void Matrix::playClock(byte hour, byte minute) {
    clear();
    int hour1 = hour / 10;
    int hour2 = hour % 10;

    int min1 = minute / 10;
    int min2 = minute % 10;

    drawDigit(hour1, HOUR1_X, TIME_Y);
    drawDigit(hour2, HOUR2_X, TIME_Y);
    drawColon(8, TIME_Y);
    drawDigit(min1, MIN1_X, TIME_Y);
    drawDigit(min2, MIN2_X, TIME_Y);
    FastLED.show();
}
