#ifndef MATRIX_H
#define MATRIX_H

#include <Arduino.h>
#include <FastLED.h>
#include <EffectBase.h>
#include <EffectWater/EffectWater.h>
#include <EffectSinelon/EffectSinelon.h>
#include <EffectConfetti/EffectConfetti.h>
#include <EffectFire/EffectFire.h>

enum class EffectType {
    WATER,
    SINELON,
    CONFETTI,
    FIRE
}; 

class Matrix{
public:
    using EffectFunc = void (Matrix::*)();

    void init();
    void drawPixel(int x, int y, CRGB color);
    void clear();
    void setBrightness(int brightness);

    void showClock(byte hour, byte minute, byte second, 
                   byte day, byte month, byte year, 
                   byte dow);

    void nextEffect() {
        currentEffect = (currentEffect + 1) % effectsCount;
    }

    void update();

    EffectType getCurrentEffect() const {
        return static_cast<EffectType>(currentEffect);
    }

    const char* getEffectName() const {
    switch (getCurrentEffect()) {
        case EffectType::WATER: return "Water";
        case EffectType::SINELON: return "Sinelon";
        case EffectType::CONFETTI: return "Confetti";
        case EffectType::FIRE: return "Fire";
        default: return "Unknown";
    }
}

    void fillScreen(CRGB color);
private:
    static constexpr uint8_t MATRIX_PIN = D6;
    static constexpr int MATRIX_HEIGHT = 16;
    static constexpr int MATRIX_WIDTH = 16;
    static constexpr int MATRIX_SIZE = 256;
    int BRIGHTNESS = 255;
    CRGB leds[MATRIX_SIZE];

    EffectConfetti confetti;
    EffectFire fire;
    EffectSinelon sinelon;
    EffectWater water;

    EffectBase* effects[4];  // базовый интерфейс
    uint8_t effectsCount;
    uint8_t currentEffect;
};

#endif