#include <Matrix.h>

void Matrix::init() {
    FastLED.addLeds<WS2811, MATRIX_PIN, GRB>(leds, MATRIX_SIZE);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.clearData();
    FastLED.show();

    effects[0] = &water;
    effects[1] = &sinelon;
    effects[2] = &confetti;
    effects[3] = &fire;
    effectsCount = 4;
    currentEffect = 0;

    for (int i = 0; i < effectsCount; i++) {
        effects[i]->init();
    }
    Serial.println("Matrix initialized with WS2811 chipset on pin " + String(MATRIX_PIN));
}

void Matrix::drawPixel(int x, int y, CRGB color) {
    if(x < 0 || x > MATRIX_WIDTH || y < 0 || y > MATRIX_HEIGHT){
        Serial.println("Error: Pixel coordinates out of bounds.");
        return;
    }
    int index = y * MATRIX_HEIGHT + x;
    leds[index] = color;
    FastLED.show();
}

void Matrix::clear(){
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

void Matrix::showClock(byte hour, byte minute, byte second, byte day, byte month, byte year, byte dow)
{
}

void Matrix::fillScreen(CRGB color)
{
    for(int i = 0; i < MATRIX_SIZE; i++) 
    {
        leds[i] = color;
        FastLED.show();
        delay(1);
    }
}

void Matrix::update(){
    effects[currentEffect]->update(leds);
    FastLED.show();
}
