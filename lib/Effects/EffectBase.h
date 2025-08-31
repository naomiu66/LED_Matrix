#ifndef EFFECT_BASE_H
#define EFFECT_BASE_H

#include <FastLED.h>

class EffectBase {
public:
    virtual void init() = 0; // Initialize the effect
    virtual void update(CRGB *leds) = 0; // Update the effect state
    virtual int getPixelNumber(int x, int y, bool flip = false) {
        if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
            Serial.println("Error: Pixel coordinates out of bounds.");
            return -1;
        }

        int flippedY = (flip) ? HEIGHT - 1 - y : y;
        int index;
        if (flippedY % 2 == 0) {
            index = flippedY * WIDTH + x;
        } else {
            index = flippedY * WIDTH + (WIDTH - 1 - x);
        }

        return index;
    }
    virtual ~EffectBase() = default; // Virtual destructor for proper cleanup
protected:
    static constexpr uint8_t WIDTH = 16;
    static constexpr uint8_t HEIGHT = 16;
};

#endif