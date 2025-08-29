#ifndef MATRIX_H
#define MATRIX_H

#define FASTLED_ALLOW_INTERRUPTS 0

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

    void nextEffect() {
        currentEffect = (currentEffect + 1) % effectsCount;
    }

    void playEffect();

    void playClock(byte hour, byte minute, byte day, byte month, byte year);

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
    const uint8_t DIGITS_3X5[10][5] = {
        {0b111, 0b101, 0b101, 0b101, 0b111}, // 0
        {0b010, 0b110, 0b010, 0b010, 0b111}, // 1
        {0b111, 0b001, 0b111, 0b100, 0b111}, // 2
        {0b111, 0b001, 0b111, 0b001, 0b111}, // 3
        {0b101, 0b101, 0b111, 0b001, 0b001}, // 4
        {0b111, 0b100, 0b111, 0b001, 0b111}, // 5
        {0b111, 0b100, 0b111, 0b101, 0b111}, // 6
        {0b111, 0b001, 0b010, 0b010, 0b010}, // 7
        {0b111, 0b101, 0b111, 0b101, 0b111}, // 8
        {0b111, 0b101, 0b111, 0b001, 0b011} //9
    };

    const uint8_t COLON[5] = {
        0b000, 0b010, 0b000, 0b010, 0b000 // :
    };

    static constexpr uint8_t MATRIX_PIN = D6;
    static constexpr int MATRIX_HEIGHT = 16;
    static constexpr int MATRIX_WIDTH = 16;
    static constexpr int MATRIX_SIZE = 256;
    static constexpr int HOUR1_X = 1;
    static constexpr int HOUR2_X = 5;
    static constexpr int TIME_Y = 2;
    static constexpr int DATE_Y = 5;
    static constexpr int COLON_X = 8;
    static constexpr int COLON_Y = 6;
    static constexpr int MIN1_X = 9;
    static constexpr int MIN2_X = 13;
    int BRIGHTNESS = 255;
    CRGB leds[MATRIX_SIZE];

    EffectConfetti confetti;
    EffectFire fire;
    EffectSinelon sinelon;
    EffectWater water;

    EffectBase* effects[4];  // базовый интерфейс
    uint8_t effectsCount;
    uint8_t currentEffect;

    void drawDigit(int digit, int x, int y);
    void drawColon(int x, int y);
};

#endif